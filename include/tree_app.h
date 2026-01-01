#pragma once
#include "file_tree.h"

class TreeApp {
public:
    static int run(int argc, char *argv[]);

private:
    static void showHelp();
    static void showVersion();
    static FileTree::Options parseOptions(int argc, char* argv[]);
};
