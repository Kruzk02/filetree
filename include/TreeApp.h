#pragma once

class TreeApp {
public:
  int run(int argc, char *argv[]);

private:
  void showHelp() const;
  void showVersion() const;
};
