# ==============================================================================
# Step 1: Load and Prepare Data
# ==============================================================================
# Read the count matrix without row names first to handle duplicates
temp_counts <- read.table("GSE231339_MergedHTSeqCount.txt", header = TRUE, check.names = FALSE)

# Remove duplicate Gene IDs (keeping the first occurrence)
counts <- temp_counts[!duplicated(temp_counts[,1]), ]

# Move Gene IDs to row names and remove the first column
rownames(counts) <- counts[,1]
counts <- counts[,-1]

# Load sample metadata
colData <- read.csv("GSE231339_colData.csv", row.names = 1)

# Ensure the order of count columns matches colData rows
counts <- counts[, rownames(colData)]

# Verify alignment (Should return TRUE)
all(colnames(counts) == rownames(colData))

# ==============================================================================
# Step 2: Data Exploration and Normalization
# ==============================================================================
# Load DESeq2 (ensure it's installed via BiocManager)
library(DESeq2)

# Create DESeqDataSet object
# Note: 'condition' matches your CSV header
dds <- DESeqDataSetFromMatrix(countData = round(counts), 
                              colData = colData, 
                              design = ~ condition)

# Plot library sizes (Millions of reads)
lib_sizes <- colSums(counts) / 1e6
barplot(lib_sizes, names.arg = colnames(counts), las = 2, 
        main = "Library Sizes per Sample", col = "skyblue", 
        ylab = "Total Counts (Millions)")

# Run normalization and differential expression analysis
dds <- DESeq(dds)

# ==============================================================================
# Step 3: Differential Expression Analysis
# ==============================================================================
# Compute results comparing ITGAV_KO vs Control
res <- results(dds, contrast=c("condition", "ITGAV_KO", "Control"))

# Order by significance (padj)
resOrdered <- res[order(res$padj), ]

# Identify significant genes (padj < 0.05)
sig_genes <- subset(resOrdered, padj < 0.05)

# Print results table for screenshot
print(head(resOrdered, 10))

# ==============================================================================
# Step 4: Generate Plots
# ==============================================================================
# 1. MA Plot
plotMA(res, main="MA Plot: ITGAV_KO vs Control", ylim=c(-5,5))

# 2. Volcano Plot (Highlights significant genes in red)
plot(res$log2FoldChange, -log10(res$padj), 
     pch=20, main="Volcano Plot: ITGAV_KO vs Control", 
     xlab="log2 Fold Change", ylab="-log10 Adjusted P-value")
points(res$log2FoldChange[res$padj < 0.05], 
       -log10(res$padj[res$padj < 0.05]), 
       col="red", pch=20)
abline(h=-log10(0.05), col="blue", lty=2)

# 3. Heatmap of Top 10 DE Genes
library(pheatmap)
top10_genes <- head(rownames(resOrdered), 10)
ntd <- normTransform(dds) # Transform for visualization
pheatmap(assay(ntd)[top10_genes, ], 
         cluster_rows=TRUE, 
         cluster_cols=TRUE, 
         annotation_col=colData,
         main="Top 10 DE Genes Heatmap")

# 4. Optional PCA Plot
plotPCA(vst(dds, blind=FALSE), intgroup="condition")