#include "BoardPoinsModel.h"
#include "qdebug.h"


BoardPointsModel::BoardPointsModel()
{
	values = new QList<BoardPoint>();
}


BoardPointsModel::~BoardPointsModel()
{
	values->clear();
}

int BoardPointsModel::rowCount(const QModelIndex &) const
{
	return values->count();
}

QVariant BoardPointsModel::data( const QModelIndex &index, int role ) const
{

	QVariant value;

	switch ( role )
	{
	case Qt::DisplayRole: //string
		{
			QPointF point=this->values->at(index.row()).getPointCoord();
			QString pointCoord = QString("X=%1, Y=%2")
				.arg(point.x(),0,'f',1)
				.arg(point.y(),0,'f',1); 
			value = this->values->at(index.row()).getPointTag() + "(" + pointCoord + ")" ;
		}
		break;

	case Qt::UserRole: //data
		{
			value = this->values->value(index.row()).getPointCoord();
		}
		break;

	default:
		break;
	}

	return value;
}


void BoardPointsModel::append(const BoardPoint& value)

{

	int newRow = this->values->count()+1;

	this->beginInsertRows(QModelIndex(), newRow, newRow);
	values->append(value);
	endInsertRows();

}



void BoardPointsModel::deleteRow(int idx)
{
	int rowIdx = 0;
	QString pointTag = QString("Point (%1)").arg(idx);	
	QList<BoardPoint>::iterator i;
	for (i = values->begin(); i != values->end(); ++i)
	{
		if((*i).getPointTag().contains( pointTag,Qt::CaseInsensitive)) break;
		rowIdx++;
	}
	this->beginRemoveRows(QModelIndex(), rowIdx,rowIdx);

	(*this->values).removeAt(rowIdx);

	this->endRemoveRows();
}
void BoardPointsModel::clear()
{
	int rowIdx = 0;
	this->removeRows(rowIdx,values->count(),QModelIndex());
}