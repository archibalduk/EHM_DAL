# EHM DAL: A data abstraction layer for Eastside Hockey Manager 1
![GitHub last commit](https://img.shields.io/github/last-commit/archibalduk/EHM_DAL?style=flat-square) ![GitHub](https://img.shields.io/github/license/archibalduk/EHM_DAL?style=flat-square) ![GitHub top language](https://img.shields.io/github/languages/top/archibalduk/EHM_DAL?style=flat-square)

EHM DAL is an unofficial data abstraction layer for Eastside Hockey Manger 1 databases and saved games which you can integrate into your own Qt/C++ projects. EHM DAL provides a library of functions which enable an EHM database or saved game to be loaded and parsed without needing to code any of your own file i/o functions or any database structures. Parsing a database or saved game is as simple as integrating the EHM DAL library into your Qt/C++ project and then adding the following code:

```
// The following code will open and process a database
auto db{ehm_db::Database()};
return db.read("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Eastside Hockey Manager\\data\\database\\database.db");

// The following code will open and process a saved game
auto sav{ehm_sav::SavedGame()};
return sav.read("C:\\Users\\archibalduk\\Documents\\Sports Interactive\\EHM\\games\\Test.sav");
```

EHM DAL's database table classes inherit from [QAbstractTableModel](https://doc.qt.io/qt-6/qabstracttablemodel.html) and is therefore compatible [Qt's model/view architecture](https://doc.qt.io/qt-6/model-view-programming.html). This means that database tables can be easily assigned to Qt's view widgets such as [QTableView](https://doc.qt.io/qt-6/qtableview.html).

Data can be accessed using [QModelIndex](https://doc.qt.io/qt-6/qmodelindex.html) or EHM DAL's Pointer class.

**Visit the [EHM DAL wiki](https://github.com/archibalduk/EHM_DAL/wiki) for class references, guides and tutorials.**

## Features
1. Read-only access to the EHM database and saved games;
2. Access binary data for each saved game table for parsing by the user's own code;
3. Various search functions for searching and filtering data; and
4. Export custom spreadsheets to csv or xlsx format.

## Limitations
1. No editing is currently possible (limited editing is planned for a future release);
2. No access to playable league-related structures; and
3. Few details of EHM saved game tables are known and will therefore require the user to figure out the structure and implement their own code.

## System Requirements
* [Qt6](https://www.qt.io/download-open-source) (msvc 2019 build or higher)
* [Microsoft Visual Studio 2022](https://visualstudio.microsoft.com/vs/community/) or [Microsoft Visual Studio Build Tools 2022](https://visualstudio.microsoft.com/downloads/?q=build+tools#build-tools-for-visual-studio-2022)

## Author
[@archibalduk](https://www.github.com/archibalduk)

## License
[GNU General Public License v3.0](https://choosealicense.com/licenses/gpl-3.0/)
