# Vulkan2D
Basic Vulkan 2D Framework

-------------------------------------------------------------------------------------

Vulkan API target: 1.4 / Vulkan API ターゲットバージョン: 1.4

-------------------------------------------------------------------------------------
Dependencies / 依存関係

- Vulkan SDK / Vulkan SDK  
- CMake 3.16+ / CMake 3.16以上
- GLFW 3.4+ / GLFW 3.4以上
- GLM / GLM
- SDL3 / SDL3
- fmtlib / fmtlib

-------------------------------------------------------------------------------------
Build Instructions  /　ビルド手順

To create the builds　first go go to the project root via the terminal and use the following cmake commands for release and debug builds<br>
ビルドを作りたい時はターミナルでプロジェクトのディレクトリまで移動し下記のCMAKEのコマンドを使用してください

  - Debug/デバッグ用 ： cmake -DCMAKE_BUILD_TYPE=Debug -B build-debug 
  - Release/リリース用 ： cmake -DCMAKE_BUILD_TYPE=Release -B build-release

You can replace build-debug and build-relase with a directory name you want to keep the builds in
the command will automatically create the directory and set the directory ready to build the application<br>
ビルド先を指定したい場合はbuild-debug や　build-releaseを好きなディレクトリ名に変更してください
ビルド先のディレクトリは自動で作られるため事前に作る必要はございません

After using the debug/release commands use the following the commands to build the app<br>
上記のコマンドをターミナルで入力したあとは下記のコマンドでアプリをビルドしてください

  - cmake --build build-debug
  - cmake --build build-release

replace target-directory with the directory you want to build the app<br>
自分でターゲットディレクトリ場合はtarget-directoryを自分のものと入れ替えてください

--------------------------------------------------------------------------------------
