#pragma once

// Application headers
namespace ehm_dal::column_data {
class ColumnData;
}
namespace ehm_dal::database {
class DatabaseVersion;
}
namespace ehm_dal::tables {
enum class TableIndex : char;
}

// Qt headers
class QDataStream;
class QModelIndex;
#include <QString>
#include <QVariant>
#include <type_traits>

namespace ehm_dal::schema {

template<typename T>
concept IntegralNumber = std::is_integral<T>::value;

// -- Table item/record --- //
/*!
 * \brief The AbstractTableItem class represents a row in a Table with an id field.
 */
class AbstractTableItem
{
public:
    /*!
     * \brief Default constructor.
     */
    AbstractTableItem();
    /*!
     * \brief Default destructor.
     */
    virtual ~AbstractTableItem();

    // Child data
    /*!
     * \brief Adds the child item `item` from the `child_table` to the present tree table. 
     * This represents a tree relationship between the child 'item' from the `child table` and the present table.
     * \param item child item to be added
     * \param child_table source table
     */
    virtual void addChildItem(std::shared_ptr<AbstractTableItem> item,
                              const ehm_dal::tables::TableIndex child_table);
    /*!
     * \brief Returns child data stored under the given `role` for the selected `index`.
     * \param index of the child item
     * \param role item data role. `Qt::DisplayRole` and `Qt::EditRole` are the most frequently used
     * \param column_data relating to the child schema
     * \param child_table containing the child data
     * \return a `QVariant` containing a copy of the data.
     */
    virtual QVariant childData(const QModelIndex &index,
                               qint32 role,
                               ehm_dal::column_data::ColumnData *column_data,
                               const ehm_dal::tables::TableIndex child_table) const;
    /*!
     * \brief Returns the item id number for the child data under the related `child_table`.
     * \param child_table
     */
    virtual qint32 childItemId(const ehm_dal::tables::TableIndex child_table) const;
    /*!
     * \brief Returns the number of related child items in respect of `child_table`.
     * \param child_table
     */
    virtual qint32 childRowCount(const ehm_dal::tables::TableIndex child_table) const;
    /*!
     * \brief Sets the `role` data for the child item at `index` to `value`.
     * \param index the selected index
     * \param value value to apply to the item
     * \param role item data role; typically `Qt::EditRole`
     * \param modified_columns container for storing column ids of any additional columns updated
     * \param column_data relating to the column
     * \param child_table the child's table
     * \return whether or not any data was successfully set
     */
    virtual bool setChildData(const QModelIndex &index,
                              const QVariant &value,
                              const qint32 role,
                              std::vector<qint32> &modified_columns,
                              ehm_dal::column_data::ColumnData *column_data,
                              const ehm_dal::tables::TableIndex child_table);

    // File i/o
    /*!
     * \brief Reads a table row from the `QDataStream`.
     * \param in `QDataStream` to be parsed
     * \param version EHM database version
     * \return whether or not the parsing was successful
     */
    virtual bool read(QDataStream &in, ehm_dal::database::DatabaseVersion &version);
    /*!
     * \brief Writes a table row to the `QDataStream`.
     * \param out `QDataStream` to be output to
     * \param version EHM database version
     * \return whether or not the out was successful
     */
    virtual bool write(QDataStream &out, ehm_dal::database::DatabaseVersion &version);

    // Get data - item attributes
    /*!
     * \brief Returns the row id. The first row of a table is 0, the second row is 1, etc.
     * \return the row id
     */
    inline qint32 id() const { return id_; }
    /*!
     * \brief Returns the row id in a manner compatible with QAbstractTableModel item roles.
     * This is generally unecessary and `qint32 AbstractTableItem::id()` should be used where possible.
     * \param role Item data role.
     * \return a `QVariant` containing a copy of the data.
     */
    QVariant id(const qint32 role);
    /*!
     * \brief Returns the row's display text. This provides a convenient way to obtain a simple description of the row.
     * \return the row display text.
     */
    virtual QString text() const = 0;
    Q_DECL_DEPRECATED QString displayText() const { return text(); } // TODO to be deprecated
    /*!
     * \brief Returns the row's unique database id. Not all tables use a uid.
     * \return the row unique id. A uid of -1 denotes that no uid has been set.
     */
    virtual qint32 uid() const;

    // Get data
    /*!
     * \brief Returns the row's data stored under the given `role` for the column.
     * \param column the selected column
     * \param role item data role. `Qt::DisplayRole` and `Qt::EditRole` are the most frequently used
     * \return a `QVariant` containing a copy of the data
     */
    QVariant data(const qint32 column,
                  qint32 role,
                  ehm_dal::column_data::ColumnData *column_data) const;
    /*!
     * \brief Returns the row's data stored under the given `role` for the column referred to by the `index`.
     * \param index Index of the selected column. The index's row is disregarded
     * \param role item data role. `Qt::DisplayRole` and `Qt::EditRole` are the most frequently used
     * \return a `QVariant` containing a copy of the data.
     */
    virtual QVariant data(const QModelIndex &index,
                          qint32 role,
                          ehm_dal::column_data::ColumnData *column_data) const;

    // Identifier
    /*!
     * \brief Returns the item's text identifier for matching against.
     */
    virtual QString identifier() const;
    /*!
     * \brief Returns a list of all of the item's identifiers for matching against.
     * This includes the main `identifier()` string as well as any alternatives.
     */
    virtual QStringList identifierList() const;
    // TODO implement
    /*QString personIdentifier(const QString &first_name,
                             const QString &second_name,
                             const Date &date_of_birth) const;
    QStringList personIdentifierList(const QString &first_name,
                                     const QString &second_name,
                                     const Date &date_of_birth,
                                     const Year &year_of_birth) const;*/

    // Initialisation
    /*!
     * \brief Initialises the table item members. This only needs to be called once per item.
     * \return `true` if members were initialised or `false` if nothing requires initialising.
     */
    inline virtual bool init() = 0;
    /*!
     * \brief Initialises the table item and allocates and item id to `new_id` and a uid (if applicable) and then calls `init()`.
     * This should be called whenever adding a new item to a table. This should not be called during file i/o.
     * \param new_id Id number to be allocated to the item
     * \return `true` if members were initialised or `false` if nothing requires initialising.
     */
    bool alloc(const qint32 new_id);

    // Parent data
    /*!
     * \brief Returns the item id of the items parent item. Applies to tree structures only.
     */
    virtual qint32 parentItemId() const;

    // Set data
    /*!
     * \brief Sets the `role` data for the item at `column` to `value`.
     * \param column the selected column
     * \param value value to apply to the item
     * \param role item data role; typically `Qt::EditRole`
     * \param modified_columns container for storing column ids of any additional columns updated
     * \param column_data relating to the column
     * \return whether or not any data was successfully modified
     */
    bool setData(const qint32 column,
                 const QVariant &value,
                 qint32 role,
                 std::vector<qint32> &modified_columns,
                 ehm_dal::column_data::ColumnData *column_data);
    /*!
     * \brief Sets the `role` data for the item at `index` to `value`.
     * \param index the selected index
     * \param value value to apply to the item
     * \param role item data role; typically `Qt::EditRole`
     * \param modified_columns container for storing column ids of any additional columns updated
     * \param column_data relating to the column
     * \return whether or not any data was successfully modified
     */
    virtual bool setData(const QModelIndex &index,
                         const QVariant &value,
                         qint32 role,
                         std::vector<qint32> &modified_columns,
                         ehm_dal::column_data::ColumnData *column_data);

    // Validation
    /*!
     * \brief Fixes any known errors with the item. E.g. errors introduced with a prior version of EHM DAL or the Editor.
     */
    virtual void fixErrors() { return; }

protected:
    // Item attributes
    qint32 id_; // Record id

    // Get data
    inline virtual bool deletable() const { return false; }
    template<IntegralNumber T>
    QVariant fromHexVector(const std::vector<T> &raw_data, const qint32 role) const;
    /*!
     * \brief Returns a `value` as a `QVariant` if the `role` is `Qt::DisplayRole` or `Qt::EditRole`. A blank `QVariant` is returned if another `role` is selected.
     * \param value Value to be returned
     * \param role Data role
     * \return a `QVariant`
     */
    QVariant fromValue(const QVariant &value, const qint32 role) const;

    // Operator overloading (Data stream)
    // This is solely for the purposes of reading/writing the record id for child items
    friend QDataStream &operator>>(QDataStream &in, AbstractTableItem &data);
    friend QDataStream &operator<<(QDataStream &out, const AbstractTableItem &data);

private:
    // Get data
    virtual QVariant internalData(const qint32 column, const qint32 role) const = 0;

    // Set data
    virtual bool setInternalData(const qint32 column,
                                 const QVariant &value,
                                 const qint32 role,
                                 std::vector<qint32> &modified_columns);
};

// File i/o
QDataStream &operator>>(QDataStream &in, ehm_dal::schema::AbstractTableItem &data);
QDataStream &operator<<(QDataStream &out, const ehm_dal::schema::AbstractTableItem &data);

// --- Get vector of numbers as a string --- //
template<IntegralNumber T>
QVariant AbstractTableItem::fromHexVector(const std::vector<T> &raw_data, const qint32 role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    QStringList buffer;
    for (const auto &itr : raw_data)
        buffer << QString("%1").arg(static_cast<quint8>(itr), 2, 16, QLatin1Char('0'));

    return buffer.join(QStringLiteral(" "));
}

} // namespace ehm_dal::schema


