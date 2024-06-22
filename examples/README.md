# EHM DAL: Example projects/code
The sub-folders within this `examples` folder contain various example Qt projects incorporating EHM DAL. Each example includes readme.md file explaining the purpose of the example.

## How to compile a project
1. Download the source code from [here](https://github.com/archibalduk/EHM_DAL/archive/refs/heads/main.zip).
1. Open the downloaded `.zip` file and navigate to the `examples` sub-folder.
1. Extract the desired project sub-folder to a location of your choice.
1. Create a new sub-folder named `lib` within the downloaded project folder.
1. Download the latest version of EHM DAL from the [Releases page](https://github.com/archibalduk/EHM_DAL/releases) and extract the contents of the downloaded EHM DAL `.zip` into your `lib` folder.
1. Open the `.pro` file in Qt Creator.
1. Press `Ctrl + R` in Qt Creator to build and run the application.

## Project folder structure
If you have followed the steps above correctly then your project folder will look a bit like this:

```
├── 01-01_Simple_Table_View [or whichever project sub-folder you extracted]
│   ├── lib
│   │   ├── ehm_dal
│   │   │   ├── include
│   │   │   ├── ehm_dal.lib
│   │   │   ├── ehm_dal.pri
│   │   │   ├── ehm_dal_debug.lib
│   │   ├── qxlsx
│   │   │   ├── include
│   │   │   ├── QXlsx.lib
│   │   │   ├── qxlsx.pri
│   │   │   ├── QXlsx_debug.lib
├── .gitignore
├── 01-01_Simple_Table_View.pro
├── readme.md
├── main.cpp
├── [various other .h and .cpp files]
```

**Visit the [EHM DAL documentation](https://archibalduk.github.io/EHM_DAL/annotated.html) for details of the various classes and functions.**

**Visit the [EHM DAL wiki](https://github.com/archibalduk/EHM_DAL/wiki) for guides and tutorials.**

## Author
[@archibalduk](https://www.github.com/archibalduk)

## Credits
EHM DAL uses [QXlsx by j2doll](https://github.com/QtExcel/QXlsx). QXlsx is licensed under the MIT license.

## License
[GNU General Public License v3.0](https://choosealicense.com/licenses/gpl-3.0/)
