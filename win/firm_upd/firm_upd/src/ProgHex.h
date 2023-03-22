#ifndef _PROG_HEX_H_
#define _PROG_HEX_H_

#include <QObject>
#include <QFile>
#include <QList>
#include <QByteArray>
#include <QtCore/QtGlobal>


class IntelHexSegment
{
public:
	IntelHexSegment() {;}
	quint32    startAdress;
	quint32    totalPages;
	QByteArray data;
};

class CprogHex : public QObject
{
	Q_OBJECT
public:
	explicit CprogHex(QObject *parent = 0);

private:
    quint8 getLineType(QString line);
	quint8 parseHexLine(QString line);
	quint32	linAddr;
	quint32	segAddr;
	quint32	nextAddr;

#if 0
	bool open(QString fileName, quint32 pageSize);
	inline void reReadAll() { segmentIdx = 0; segmentPos = 0; }
	inline void reReadSegment() { segmentPos = 0; }
	inline quint32 totalSegments() { return segments.size(); }
	inline quint32 segmentSize() { return segments.at(segmentIdx).data.size(); }
	inline quint32 segmentPages() { return segments.at(segmentIdx).totalPages; }
	inline qint32 selectNextSegment() { return selectSegment(segmentIdx + 1); }
	qint32 selectSegment(qint32 segment);
	qint32 readPage(quint32 &currentAddress, char **data, bool readAllSegments = 1);
	inline qint32 totalPages() { return pagesInFile; }
	bool ProgFile(QString fileName, quint32 pageSize);

private:
	void processHexLine(QString &line);
	quint32 getLineType(QString line);
	quint32 getLength(QString line);
	quint32 getAddress(QString line);
	quint32 getSegmentAddress(QString &line);
	quint32 getLinearAddress(QString &line);
	void checkForSkippedAddresses(quint32 address);
	QList<IntelHexSegment> segments;
	QFile file;
	quint32 linearAddress, segmentAddress, filledAddress;
	quint32 pageSize, pagesInFile;
	qint32 segmentIdx, segmentPos;
	bool oneShot;
#endif
public:
	bool progr(QFile *pFile);
signals:
	void sig_set_pb_val(quint32 val);
};

#endif // _PROG_HEX_H_
