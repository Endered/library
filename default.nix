{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell
  {
    nativeBuildInputs = with pkgs; [ clang_13 ];
  }
