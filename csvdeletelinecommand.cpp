#include <set>
#include <QObject>
#include "csvdeletelinecommand.hpp"

CSVDeleteLineCommand::CSVDeleteLineCommand(
        CSVGraphicsView* view
        , QUndoCommand *parent) :
    QUndoCommand(QString("Delete Lines"), parent)
    , view(view)
{
}

void CSVDeleteLineCommand::undo()
{
    view->showExtraHiddenItems(deleted);
}

void CSVDeleteLineCommand::redo()
{
    deleted= view->hideExtraSelectedItems();
}

int CSVDeleteLineCommand::id() const
{
    return this->ID;
}

bool CSVDeleteLineCommand::mergeWith(const QUndoCommand *other)
{
    return false; // komutlarin birlestirilmesini istemiyoruz
    CSVDeleteLineCommand const* csvother= dynamic_cast<CSVDeleteLineCommand const*>(other);
    if(csvother== 0) return false;
    std::set<int> mrg(this->deleted.begin(), this->deleted.end());
    mrg.insert(csvother->deleted.begin(), csvother->deleted.end());
    std::vector<int> vmrg(mrg.begin(), mrg.end());
    this->deleted.swap(vmrg);
    return true;
}
