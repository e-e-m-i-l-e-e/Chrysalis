#ifndef CHRYSALIS_UIEXPORTERDATA_H
#define CHRYSALIS_UIEXPORTERDATA_H

#include <functional>
#include <forward_list>

#include <QWidget>

class UIExporterData {
public:
    explicit UIExporterData(std::function<std::forward_list<QWidget*>()>&& factory);
    std::forward_list<QWidget*> widgets() const;
private:
    std::function<std::forward_list<QWidget*>()> factory_;
};

#endif //CHRYSALIS_UIEXPORTERDATA_H
