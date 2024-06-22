#pragma once

/* ***************************************
 * EHM Data Abstraction Layer
 * by Archibalduk
 * 
 * https://github.com/archibalduk/EHM_DAL
 * 
 * Example 01.02 - Simple Tree View
 * 
 * ***************************************/

#include <QAction>
#include <QMainWindow>
#include <QMenuBar>
#include <QTreeView>

/// The purpose of this example is to show how easily a database tree table can be displayed using a QTreeView widget.
/// This example additionally shows how table data can be exported to a csv/xlsx spreadsheet file.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // Menu
    QMenuBar *menu_bar_;
    QAction *open_database_action_;
    QAction *open_saved_game_action_;
    QAction *spreadsheet_export_all_columns_action_;
    QAction *spreadsheet_export_selected_columns_action_;

    // Table
    QTreeView *tree_view_;

private slots:
    // Slot functions for connecting to signal functions
    void exportSpreadsheet();
    void exportSpreadsheetSelectedColumns();
    void openDatabase();
    void openSavedGame();
};
