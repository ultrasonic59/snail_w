#ifndef _PROG_HEX_H_
#define _PROG_HEX_H_

#include <QObject>
#include <QFile>
#include <QList>
#include <QByteArray>
#include <QtCore/QtGlobal>
#include "can_cmd.h"

#define ADDR_FLASH_APP 0x080010000
#if 0
class IntelHexSegment
{
public:
	IntelHexSegment() {;}
	quint32    startAdress;
	quint32    totalPages;
	QByteArray data;
};
#endif
///==== Can cmd ====================
#define ERRASE_ADDR  0x3
#define PROG_ADDR    0x4
#define PROG_CHUNC   0x5

#define MAX_PROG_CHUNC_SIZE 6

#define MAX_NUM_BYTES 32
typedef struct bin_dat_s{
quint8 len_data;
quint8 bytes[MAX_NUM_BYTES];
}bin_data_t;

class CprogHex : public QObject
{
	Q_OBJECT
public:
	explicit CprogHex(QObject *parent = 0);

private:
    quint8 getLineType(QString line);
	quint8 parseHexLine(QString line);
	quint8 hex2bin(QString line );
	quint8 progFlash();
	quint8 progFlashChunc(quint8 *dat, quint8 len);
    quint8 setProgAddr(quint32 addres);
	quint8 erraseAddr(quint32 addres);
	quint8 sendCanCmd(can_cmd_t *dat);

	quint32	linAddr;
////	quint32	segAddr;
///	quint32	nextAddr;
	bin_data_t cur_bin_data;

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
