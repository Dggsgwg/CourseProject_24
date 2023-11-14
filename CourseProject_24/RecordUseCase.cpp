//#include "RecordUseCase.h"
//#include "DateUseCase.h"
//#include <format>
//
//string RecordUseCase::recordToString(Record record)
//{
//	DateUseCase duc = DateUseCase();
//
//	return format("|   {:<9} | {:<10} | {:<19} |  {:<1}  |   {:<9} | {:<10} |    {:<13} |    {:<6} |",
//		record.groupCode, record.personalId, record.name, record.isMale ? "Ì" : "Æ",
//		record.educationForm, duc.dateToString(record.birthdayDate),
//		duc.dateToString(record.entranceDate), record.EGEPoints);
//}
//
//string RecordUseCase::recordToFileString(Record record)
//{
//	DateUseCase duc = DateUseCase();
//
//	return format("{} {} {} {} {} {} {} {}",
//		record.groupCode, record.personalId, record.name, record.isMale ? "Ì" : "Æ",
//		record.educationForm, duc.dateToFileString(record.birthdayDate),
//		duc.dateToFileString(record.entranceDate), record.EGEPoints);
//}