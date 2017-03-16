# Setup

For this tool to work, a set of tool chains based around VirtualDub are required to be installed prior.
Two ways to install these tools: 
- [Use archive in this repo](https://github.com/MadisonTBlake/BatchStabalizer#option-1---unpack-from-archive)
- [Download/install individually](https://github.com/MadisonTBlake/BatchStabalizer#option-2---individually-download)

## Option 1 - Unpack from archive

Download the archive distributed in this repository:
https://github.com/MadisonTBlake/BatchStabalizer/blob/master/VirutalDub_Deshaker_FFMPEG.zip

Unzip the archive into a directory of your choosing.

## Option 2 - Individually download

Alternativly each individual tool can be downloaded if desired

### Download Virtual Dub

The base of the tool uses VirtualDub to perform video manipulation.
From http://www.virtualdub.org/, download the tool and unzip to a directory of your choosing.

This software was tested with V1.10.4

### Install Deshaker Plugin

With VirtualDub on computer install the Deshaker plugin.
From http://www.guthspot.se/video/deshaker.htm, download 32/64 bit version.
Unzip and place in respective `plugin32` or `plugin64` folder of your VirtualDub installation.

This software was tested with V3.1

### Install FFMpeg Input Plugin for VirtualDub

By default VirtualDub can only take in .avi files, therefore we must install a plugin to read other codecs.
Download `VirtualdubFFMpegPlugin_1848_X86_X64.zip` from https://sourceforge.net/projects/virtualdubffmpeginputplugin/files/V1848/.
Unzip the `plugin32` and `plugin64` folders directly into your VirtualDub installation folder.

### Download FFMPEG

Finally we need a tool to export the .avi that VirtualDub creates into a .mp4.
Download FFmpeg for windows from https://ffmpeg.org/download.html.

In the `bin`folder of the downloaded archive, extract `ffmpeg.exe` into your VirtualDub folder.

# Using Batch Stabalizer

# Compile From Source
