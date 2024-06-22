#include "mainwindow.h"

#include "lib/ehm_dal/include/database/column_data/club_competition_columns.h"
#include "lib/ehm_dal/include/database/database.h"
#include "lib/ehm_dal/include/database/file_io/database_file_manager.h"
#include "lib/ehm_dal/include/library_info.h"
#include "lib/ehm_dal/include/saved_game/file_io/saved_game_file_manager.h"
#include "lib/ehm_dal/include/spreadsheet/spreadsheet.h"
#include "lib/ehm_dal/include/tables/abstract_table.h"
#include "lib/ehm_dal/include/tables/table_index.h"

#include <QDebug>
#include <QFileDialog>

/* MAIN WINDOW CONSTRUCTOR
 * This function constructs the main window and adds the following to the window:
 * 1. A menu bar with a drop-down menu allowing users to (i) open a database or saved game and (ii) export table data to a spreadsheet; and
 * 2. A QTableView widget which will show the selected database table within the window.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /// Window attributes ///
    setMinimumSize(1200, 600);
    setWindowTitle(QString("Simple Table Viewer - %1 %2")
                       .arg(ehm_dal::library_info::libraryShortName(),
                            ehm_dal::library_info::libraryVersion()));

    /// Menu bar ///
    menu_bar_ = new QMenuBar(this);
    setMenuBar(menu_bar_);

    /// Menu bar -> File menu ///
    auto file_menu{menu_bar_->addMenu("&File")};

    // Create a new QAction which will be shown in the File menu.
    // Clicking on this QAction will trigger the openDatabase() function.
    open_database_action_ = new QAction("Open &database...", this);
    QObject::connect(open_database_action_, &QAction::triggered, this, &MainWindow::openDatabase);
    file_menu->addAction(open_database_action_);

    // Create a new QAction which will be shown in the File menu.
    // Clicking on this QAction will trigger the openSavedGame() function.
    open_saved_game_action_ = new QAction("Open saved &game...", this);
    QObject::connect(open_saved_game_action_, &QAction::triggered, this, &MainWindow::openSavedGame);
    file_menu->addAction(open_saved_game_action_);

    /// Menu bar -> Tools menu ///
    auto tools_menu{menu_bar_->addMenu("&Tools")};

    // Create a new QAction which will be shown in the Tools menu.
    // Clicking on this QAction will trigger the exportSpreadsheet() function.
    spreadsheet_export_all_columns_action_ = new QAction("&Export to spreadsheet...", this);
    QObject::connect(spreadsheet_export_all_columns_action_,
                     &QAction::triggered,
                     this,
                     &MainWindow::exportSpreadsheet);
    tools_menu->addAction(spreadsheet_export_all_columns_action_);

    // Create a new QAction which will be shown in the Tools menu.
    // Clicking on this QAction will trigger the exportSpreadsheetSelectedColumns() function.
    spreadsheet_export_selected_columns_action_
        = new QAction("Export to spreadsheet (selected &columns)...", this);
    QObject::connect(spreadsheet_export_selected_columns_action_,
                     &QAction::triggered,
                     this,
                     &MainWindow::exportSpreadsheetSelectedColumns);
    tools_menu->addAction(spreadsheet_export_selected_columns_action_);

    /// Table view ///
    table_view_ = new QTableView(this);
    setCentralWidget(table_view_);

    // Assign the selected table below to the table_view_.
    // Let's use the Club Competitions table for the purposes of this example.
    ehm_dal::Database db;
    table_view_->setModel(db.table(ehm_dal::tables::TableIndex::CLUB_COMPETITIONS).get());
}

/* MAIN WINDOW CONSTRUCTOR
 * Nothing to see here.
 * The various class members will be auto-deleted as part of Qt's garbage collection. Hence no explicit `delete` calls here.
 */
MainWindow::~MainWindow() {}

/* FUNCTION: EXPORT SPREADSHEET (all columns)
 * Generates a new spreadsheet and populates it with the entirety of the Club Competitions data table.
 */
void MainWindow::exportSpreadsheet()
{
    ehm_dal::spreadsheet::Spreadsheet spreadsheet;

    // Let's use the Club Competitions table
    ehm_dal::Database db;
    auto table{db.table(ehm_dal::tables::TableIndex::CLUB_COMPETITIONS)};

    // Show a window dialog prompting the user to select the destination for saving the spreadsheet.
    // The `table->attributes()->name()` function takes the name of the table and this is then used as default file name for saving.
    // Abort if the user clicks `Cancel` (`showSaveDialog()` will return false if cancelled).
    // By adding the data to the spreadsheet only after this function, we avoid wasting time populating the spreadsheet with data
    // in the event the user has clicked `Cancel`.
    if (!spreadsheet.showSaveDialog(QString("%1.xlsx").arg(table->attributes()->name())))
        return;

    // Add a header row to the spreadsheet based on the table's column names
    spreadsheet.addHeader(table.get());
    // Add the entirety of the table data to the spreadsheet
    spreadsheet.add(table.get());

    // Save the spreadsheet data to the file.
    if (spreadsheet.write())
        qInfo() << "Spreadsheet successfully saved";
    else
        qInfo() << "Unable to save the spreadsheet";
}

/* FUNCTION: EXPORT SPREADSHEET (selected columns)
 * Generates a new spreadsheet and populates it with just a few columns of data of the Club Competitions data table.
 */
void MainWindow::exportSpreadsheetSelectedColumns()
{
    // This is a very similar function to `exportSpreadsheet()` but with the key difference that here we generate a list of
    // columns we want to export. This will result in just those selected columns being exported.
    ehm_dal::spreadsheet::Spreadsheet spreadsheet;

    ehm_dal::Database db;
    auto table{db.table(ehm_dal::tables::TableIndex::CLUB_COMPETITIONS)};

    if (!spreadsheet.showSaveDialog(QString("%1.xlsx").arg(table->attributes()->name())))
        return;

    // Here's where the function is different to `exportSpreadsheet()` above:
    // First we create a list of what columns we want to export.
    // We then pass this list to the same `addHeader()` and `add()` functions as before.
    std::vector<qint32> column_list{ehm_dal::column_data::ClubCompetitionColumns::Name,
                                    ehm_dal::column_data::ClubCompetitionColumns::Nation,
                                    ehm_dal::column_data::ClubCompetitionColumns::Classification,
                                    ehm_dal::column_data::ClubCompetitionColumns::Reputation};

    spreadsheet.addHeader(table.get(), column_list);
    spreadsheet.add(table.get(), column_list);

    if (spreadsheet.write())
        qInfo() << "Spreadsheet successfully saved";
    else
        qInfo() << "Unable to save the spreadsheet";
}

/* FUNCTION: OPEN DATABASE
 * This function uses the DatabaseFileManager to display a dialog window allowing the user to select a database file to open.
 * The DatabaseFileManager will then proceed to open and process the database file.
 */
void MainWindow::openDatabase()
{
    ehm_dal::file_io::DatabaseFileManager db_file_manager;

    // Display the file selection dialog window and process the selected database file
    if (db_file_manager.open(this))
        qInfo() << "Database successfully opened";
    else
        qInfo() << "Unable to open the database";
}

/* FUNCTION: OPEN SAVED GAME
 * This function uses the SavedGameFileManager to display a dialog window allowing the user to select a saved game file to open.
 * The SavedGameFileManager will then proceed to open and process the saved game file.
 */
void MainWindow::openSavedGame()
{
    ehm_dal::file_io::SavedGameFileManager sg_file_manager;

    // Display the file selection dialog window and process the selected saved game file
    if (sg_file_manager.open(this))
        qInfo() << "Saved game successfully opened";
    else
        qInfo() << "Unable to open the saved game";
}
