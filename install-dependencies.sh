#!/bin/bash

# Update Homebrew
brew update

# For development

# Install cmake
brew cmake;

# Install IWYU
brew include-what-you-use;

# For the product

brew install sfml

echo "All dependencies have been installed."
