This is a Windows tool that monitors a given directory and automatically runs Deshaker stabilization filter on any new video files.
This tool runs in the background and will only be called upon when the directory it is monitoring has a new video file added to it.

Word of warning: Deshaking a video file can take quite some time, on the order of hours, and can consume quite a bit of computer resourses. This tool contains functionality that can halt all conversions and stop monitoring that can be used if computer resourses are needed in the middle of a conversion.

- https://github.com/MadisonTBlake/BatchStabilizer/blob/master/README.md#setup Details how to setup the tools needed by this application
- https://github.com/MadisonTBlake/BatchStabilizer/blob/master/README.md#setup Gives a brief rundown on how to use this tool after it is installed

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

This program is mostly designed to stay running in the background and continuously monitor the given folder for changes.

By default, the installer will add the program to auto start upon boot up.

However for it to work you must set up the directories. The values you enter here will persist when the application is closed or machine restarts.

To edit the values bring the tool up into foreground mode by right clicking and restoring on icon in toolbar. If there is no icon then the application is not running.

With the dialog up. Set the virtual dub folder to be the folder configured above and set the directory to monitor to be a directory of your choice. It is recomened you choose a mostly empty folder and add videos you want to stabalize later. This tool will stabalize every .mpg in the given folder.

Stabalization may take quite some time, and can consume quite a bit of resourses while doing so. If you need you computer's resourses for whatever reason, press "Stop" on the dialog or "Stop Scan" on the context menu to halt any current action. The text will then change to "Start" and "Start Scan", which you can press at a later time to resume monitoring. Stoping the app does stops everything, if it where almost done with a given pass, progress will restart.

# Compile From Source
