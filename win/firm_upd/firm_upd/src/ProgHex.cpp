#include <QTextStream>
#include <QThread>
#include <QDebug>
#include "progHex.h"


CprogHex::CprogHex(QObject *parent) : 
			QObject(parent),
	        linAddr(0),
			segAddr(0),
			nextAddr(0)

{

}

quint8 CprogHex::getLineType(QString line)
{
////	line.remove(0, 7);
////	line.remove(2, 64);
////	return line.toUInt();
return	line.mid(6, 2).toULong(0, 16);
}

#define HEX_OK			0
#define END_OF_FILE		1
#define ERR_TYPE_REC	3

quint8 CprogHex::parseHexLine(QString line)
{
quint8 rez=0;
quint8 crc8=0;
line.remove(':');
for(int cc =0; cc < line.length(); cc +=2)
	{
	crc8 += line.mid(cc, 2).toUShort(0, 16);
	}
////QThread::msleep(1);
if(crc8 == 0)
   {
	quint8 lenData= line.mid(0, 2).toULong(0, 16);
	quint8 lineType= line.mid(6, 2).toULong(0, 16);
	quint32 offsAddr=line.mid(2, 4).toULong(0, 16);
	quint32 tData	=line.mid(8, lenData * 2).toULong(0, 16);
	quint32 Address = linAddr + segAddr + offsAddr;

	switch(lineType)
		{
		case 0: /// Data
	///		sRes += (sHexFileStr.mid(8, bLenData * 2) + "\n");
			rez = HEX_OK;
////				qDebug() << "Data " ;
		break;
		case 1: //
				rez = END_OF_FILE;
					qDebug() << "END_OF_FILE " ;
		break;

		case 2: // Extended Segment Address Record
			segAddr = tData << 4; // *16
			rez = HEX_OK;
			qDebug() << "Extended Segment Address Record " ;
			break;

		case 3: // Start Segment Address Record
////				sRes ="[Start Segment Address: 0x" + DWORD2Hex(dwData) + "]\n";
			qDebug() << "Start Segment Address Record " ;

			break;

		case 4: // Extended Linear Address Record
				linAddr = tData << 16; // *65536
			qDebug() << "Extended Linear Address Record " ;
			break;

		case 5: // Start Linear Address Record
////				sRes ="[Start Linear Address: 0x" + DWORD2Hex(dwData) + "]\n";
			qDebug() << "Start Linear Address Record " ;
			break;

		case 32: // ROM code, used by Samsung SAMA assembler
		case 34: // Extension code, used by Samsung Smart Studio microcontroller development system

		default:
			rez = ERR_TYPE_REC;
			qDebug() << "Unknown type record: " << lineType;
		////	sRes ="<Unknown type record>\n";
		}
		nextAddr = Address + lenData;
			qDebug() << "nextAddr :" << nextAddr<< "Address :"<<Address <<"lenData" << lenData;

   }
else
   {
	qDebug() << "Error crc " ;

   }
////	line.remove(0, 7);
////	line.remove(2, 64);
////	return line.toUInt();
////return	line.mid(6, 2).toULong(0, 16);
return rez;
}


bool CprogHex::progr(QFile *pFile)
{
QString tstr;
quint32 cur_pos=0;
QTextStream in(pFile);
while(!in.atEnd())
	{
	tstr=in.readLine();
	parseHexLine(tstr);
	cur_pos += tstr.length();
////	qDebug() << "cur_pos: " << cur_pos;
	emit sig_set_pb_val(cur_pos);
	}
return true;
}


#if 0
bool CProgHex::open(QString fileName, quint32 pageSize)
{
	linearAddress = 0;
	segmentAddress = 0;
	filledAddress = 0;
	pagesInFile = 0;
	oneShot = 0;
	CProgHex::pageSize = pageSize;
	reReadAll();
	segments.clear();
	segments.append(IntelHexSegment());

	file.setFileName(fileName);
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug("Can't open file");
		return 0;
	}
	QTextStream in(&file);

	QString line = in.readLine();
	while(!line.isNull()) {
		if (line.startsWith(":"))
			processHexLine(line);
		line = in.readLine();
	}
	file.close();

	QList<IntelHexSegment>::iterator i;
	for (i=segments.begin(); i!=segments.end(); i++) {
		(*i).totalPages = (*i).data.size() / pageSize;
		pagesInFile+= (*i).totalPages;
	}

	return 1;
}

bool CProgHex::ProgFile(QString fileName, quint32 pageSize)
{
return true;
}

void CProgHex::processHexLine(QString &line)
{
	quint32 length, address, i;
	bool ok;

	switch (getLineType(line)) {
		case 4: linearAddress = getLinearAddress(line); break;
		case 2: segmentAddress = getSegmentAddress(line); break;
		case 5:
		case 1:
			// pad the very last page to be on a page boundary
			while (segments.last().data.size() % pageSize)
				segments.last().data.append(0xFF);
			break;
		case 0:
			length = getLength(line);
			address = linearAddress + segmentAddress + getAddress(line);
			if (!oneShot) { // initialize on first line
				oneShot = 1;
				filledAddress = address;
				segments.last().startAdress = address;
			}
			checkForSkippedAddresses(address);
			filledAddress+= length;
			i = 9;
			while (length) {
				QString temp;
				temp = line;
				temp.remove(0, i);
				temp.remove(2, 64);
				segments.last().data.append(temp.toInt(&ok, 16));
				i+= 2;
				length--;
				address++;
			}
			//qDebug() << QString::number(address, 16) << line;
			break;
	}
}


quint32 CProgHex::getLength(QString line)
{
	bool ok;

	line.remove(0, 1);
	line.remove(2, 64);
	return line.toInt(&ok, 16);
}

quint32 CProgHex::getAddress(QString line)
{
	bool ok;

	line.remove(0, 3);
	line.remove(4, 64);
	return line.toInt(&ok, 16);
}

quint32 CProgHex::getSegmentAddress(QString &line)
{
	bool ok;

	line.remove(0, 9);
	line.remove(4, 64);
	return line.toInt(&ok, 16);
}

quint32 CProgHex::getLinearAddress(QString &line)
{
	return getSegmentAddress(line) * 0x10000;
}

void CProgHex::checkForSkippedAddresses(quint32 address)
{
	if (address != filledAddress) {
		quint32 nextPageAddress = filledAddress + (pageSize - 1);
		nextPageAddress&= ~(pageSize - 1);

		// Fill up to address or nextPageAddress, which ever comes first.
		for (;(filledAddress < nextPageAddress) && (filledAddress < address); filledAddress++)
			segments.last().data.append(0xFF);

		// if address is not page aligned, set nextPageAddress to the preceeding page boundary of address.
		nextPageAddress = address & ~(pageSize - 1);

		// check for a jump in pages
		if ((address - filledAddress) >= pageSize) {
			segments.append(IntelHexSegment());
			segments.last().startAdress = nextPageAddress;
			filledAddress = nextPageAddress;
		}

		// check if address is page aligned and fill if not
		for (;filledAddress < address; filledAddress++)
			segments.last().data.append(0xFF);
	}
}

qint32 CProgHex::selectSegment(qint32 segment)
{
	if (segment < segments.size() - 1) {
		segmentIdx = segment;
		segmentPos = 0;
		return segmentIdx;
	}
	else
		return -1;
}

//quint32 getSegmentBaseAddress()

qint32 CProgHex::readPage(quint32 &currentAddress, char **data, bool readAllSegments)
{
	qint32 bytesAvailable = segments.at(segmentIdx).data.size() - segmentPos;

	if (!bytesAvailable && readAllSegments) {
		if (segmentIdx < segments.size() - 1) {
			segmentIdx++;
			segmentPos = 0;
			bytesAvailable = segments.at(segmentIdx).data.size() - segmentPos;
		}
	}

	currentAddress = segments.at(segmentIdx).startAdress + segmentPos;
	*data = (char*)segments.at(segmentIdx).data.data() + segmentPos;

	if (bytesAvailable > (signed)pageSize)
		bytesAvailable = pageSize;
	segmentPos+= bytesAvailable;

	return bytesAvailable;
}
#endif