#ifndef CSVDELETELINECOMMAND_HPP
#define CSVDELETELINECOMMAND_HPP

#include <QUndoCommand>
#include <vector>
#include <csvgraphicsview.hpp>

class CSVDeleteLineCommand : public QUndoCommand
{   
    CSVGraphicsView* view;
    std::vector<int> deleted;
    enum{ ID= 42 };
public:
    CSVDeleteLineCommand(CSVGraphicsView* view, QUndoCommand *parent = 0);
    void undo();
    void redo();
    int id() const;
    bool mergeWith(const QUndoCommand *other);
};

#endif // CSVDELETELINECOMMAND_HPP
