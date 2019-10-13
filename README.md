# Stardew Valley Mod Manager 2

Simple mod manager for Stardew Valley to be used with SMAPI and Content Patcher.  Originally inspired by yuukiw's StardewValleyMM in vb.NET.  And this README is from a template and needs work.

## What I've Used (and you'll need to use this code easily)
* Visual Studio Community 2019 (if you want to use the solution file)
* wxWidgets v3.0.0 or better

## Goals
#### Always
* All Buttons Have a Function
* Handle All Exceptions

#### Before first alpha release: [COMPLETE]
In order of importance.
* See Installed Mods (and State) [COMPLETE]
* Toggle Mods On/Off [COMPLETE]
* Locate Game Directory [COMPLETE]
* Locate Steam Directory [COMPLETE]
* Save Settings [COMPLETE]
* Shortcut to Mod Folders [COMPLETE]
* Shortcut to Mod Sources (Nexus/Forums) [COMPLETE]

#### Before 0.5.1 release:
* Handle exceptions if SMAPI not found [COMPLETE]
* Fix SV crash when launched from remote directory [COMPLETE]
* Rework debug message methods [COMPLETE]
* Migrate init file checks from filesystem to wxWidgets [PARTIAL]
* Specify error types in reports [COMPLETE]
* Group json error messages [COMPLETE]
* Handle relaxed manifest.json format errors [COMPLETE]
* Add mod counter [COMPLETE]
* Handle other exceptions (see bug reports) [PARTIAL]

#### Before first full release:
Not yet in order of importance.
* Allow group selection of mods for toggle [TODO]
* Auto-find Game Directory [TODO]
* Auto-find Steam Directory [TODO]
* Flag Incompatible Mods [TODO]
* Add/Delete Mods [TODO]
* Launch through Steam [COMPLETE]
* Help/About Menu Tab [TODO]
* Migrate Filesystem to wxStandardPaths [PARTIAL]

#### Maybe one day:
Not in order of importance.
* Nest mods in list (content patcher, etc) [TODO]
* Save/Load Modlist Profiles [TODO]
* Export/Import shared Modlist profiles [TODO]
* Check for mod updates [TODO]
* Donation Button? [TODO]
* XNB Support? [TODO]

## Authors
* **OkaMoez** - (https://github.com/OkaMoez)

See also the list of [contributors](https://github.com/OkaMoez/SDVMM2/contributors) who participated in this project.

## Acknowledgments
* nlohmann/json
* yuukiw/StardewValleyMM
* Stack Exchange/Overflow for teaching me to code
* wxWidgets forums (even if they delete posts that would have saved me hours of my time)
* Google, for always being there when I needed help learning code
