#!/bin/bash
set -e

# Initialize workspace mapping based on the local app directory
west init -l app

# Pull the manifest trees (includes NXP board trees)
west update

# Link the workspace engine variables to CMake
west zephyr-export

# Apply core hardware configuration patches if present
if [ -f app/.devcontainer/patches ]; then
    west patch apply
fi

# Rapid python dependency parsing using uv
uv pip install -r deps/zephyr/scripts/requirements.txt

# Terminal prompt workflow enhancements
echo "alias ll='ls -lah'" >> $HOME/.bashrc
west completion bash > $HOME/west-completion.bash
echo 'source $HOME/west-completion.bash' >> $HOME/.bashrc

# Wipe internal shell command history for a clean layout
history -c
