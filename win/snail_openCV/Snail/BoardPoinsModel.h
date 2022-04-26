#pragma once
#include <QModelIndex>
#include <QAbstractListModel>
#include "BoardPoint.h"
class BoardPointsModel :	public QAbstractListModel
{
	
public:
	BoardPointsModel();
	 ~BoardPointsModel();
	int rowCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
	void append(const BoardPoint& value);
	void deleteRow(int idx);
	void clear();

private:
    QList<BoardPoint> *values;
};

