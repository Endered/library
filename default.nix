{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell
  {
    nativeBuildInputs = with pkgs; [ clang-tools online-judge-tools ];
  }
