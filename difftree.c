#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct FileNode {
    char *name;
    int isDir;
    struct FileNode *next;
    struct FileNode *children;
} FileNode;

FileNode* createNode(const char *name, int isDir) {
    FileNode *node = (FileNode*)malloc(sizeof(FileNode));
    node->name = strdup(name);
    node->isDir = isDir;
    node->next = NULL;
    node->children = NULL;
    return node;
}

void freeNode(FileNode *node) {
    if (node) {
        free(node->name);
        freeNode(node->next);
        freeNode(node->children);
        free(node);
    }
}

FileNode* buildTree(const char *dirPath) {
    DIR *dir = opendir(dirPath);
    if (!dir) {
        perror("opendir");
        return NULL;
    }

    struct dirent *entry;
    FileNode *root = createNode(dirPath, 1);
    FileNode *current = NULL;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char fullPath[PATH_MAX];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", dirPath, entry->d_name);

        struct stat statbuf;
        if (stat(fullPath, &statbuf) != 0) {
            perror("stat");
            continue;
        }

        FileNode *node = createNode(entry->d_name, S_ISDIR(statbuf.st_mode));

        if (S_ISDIR(statbuf.st_mode)) {
            node->children = buildTree(fullPath);
        }

        if (!current) {
            root->children = node;
        } else {
            current->next = node;
        }
        current = node;
    }

    closedir(dir);
    return root;
}

void compareTrees(FileNode *tree1, FileNode *tree2, const char *base1, const char *base2) {
    FileNode *child1 = tree1 ? tree1->children : NULL;
    FileNode *child2 = tree2 ? tree2->children : NULL;

    while (child1 || child2) {
        if (child1 && (!child2 || strcmp(child1->name, child2->name) < 0)) {
            printf("只在 %s 存在：%s\n", base1, child1->name);
            child1 = child1->next;
        } else if (child2 && (!child1 || strcmp(child1->name, child2->name) > 0)) {
            printf("只在 %s 存在：%s\n", base2, child2->name);
            child2 = child2->next;
        } else {
            if (child1->isDir && child2->isDir) {
                char path1[PATH_MAX], path2[PATH_MAX];
                snprintf(path1, sizeof(path1), "%s/%s", base1, child1->name);
                snprintf(path2, sizeof(path2), "%s/%s", base2, child2->name);
                compareTrees(child1, child2, path1, path2);
            }
            child1 = child1->next;
            child2 = child2->next;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <dir1> <dir2>\n", argv[0]);
        return 1;
    }

    FileNode *tree1 = buildTree(argv[1]);
    FileNode *tree2 = buildTree(argv[2]);

    if (!tree1 || !tree2) {
        fprintf(stderr, "Error building directory trees.\n");
        freeNode(tree1);
        freeNode(tree2);
        return 1;
    }

    compareTrees(tree1, tree2, argv[1], argv[2]);

    freeNode(tree1);
    freeNode(tree2);

    return 0;
}
