#include "pingDcps.h"
#if EORB_USE_EXPLICIT_TEMPLATES
template class DDS_DCPSUVLSeq <PingType, struct PingTypeSeq_uniq_>;
#endif

const char * PingTypeTypeSupportInterface::_local_id = "IDL:/PingTypeTypeSupportInterface:1.0";

PingTypeTypeSupportInterface_ptr PingTypeTypeSupportInterface::_duplicate (PingTypeTypeSupportInterface_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean PingTypeTypeSupportInterface::_local_is_a (const char * _id)
{
   if (strcmp (_id, PingTypeTypeSupportInterface::_local_id) == 0)
   {
      return TRUE;
   }

   typedef DDS::TypeSupport NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return TRUE;
   }

   return FALSE;
}

PingTypeTypeSupportInterface_ptr PingTypeTypeSupportInterface::_narrow (DDS::Object_ptr p)
{
   PingTypeTypeSupportInterface_ptr result = NULL;
   if (p && p->_is_a (PingTypeTypeSupportInterface::_local_id))
   {
      result = dynamic_cast<PingTypeTypeSupportInterface_ptr> (p);
      result->m_count++;
   }
   return result;
}

PingTypeTypeSupportInterface_ptr PingTypeTypeSupportInterface::_unchecked_narrow (DDS::Object_ptr p)
{
   PingTypeTypeSupportInterface_ptr result;
   result = dynamic_cast<PingTypeTypeSupportInterface_ptr> (p);
   result->m_count++;
   return result;
}

const char * PingTypeDataWriter::_local_id = "IDL:/PingTypeDataWriter:1.0";

PingTypeDataWriter_ptr PingTypeDataWriter::_duplicate (PingTypeDataWriter_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean PingTypeDataWriter::_local_is_a (const char * _id)
{
   if (strcmp (_id, PingTypeDataWriter::_local_id) == 0)
   {
      return TRUE;
   }

   typedef DDS::DataWriter NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return TRUE;
   }

   return FALSE;
}

PingTypeDataWriter_ptr PingTypeDataWriter::_narrow (DDS::Object_ptr p)
{
   PingTypeDataWriter_ptr result = NULL;
   if (p && p->_is_a (PingTypeDataWriter::_local_id))
   {
      result = dynamic_cast<PingTypeDataWriter_ptr> (p);
      result->m_count++;
   }
   return result;
}

PingTypeDataWriter_ptr PingTypeDataWriter::_unchecked_narrow (DDS::Object_ptr p)
{
   PingTypeDataWriter_ptr result;
   result = dynamic_cast<PingTypeDataWriter_ptr> (p);
   result->m_count++;
   return result;
}

const char * PingTypeDataReader::_local_id = "IDL:/PingTypeDataReader:1.0";

PingTypeDataReader_ptr PingTypeDataReader::_duplicate (PingTypeDataReader_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean PingTypeDataReader::_local_is_a (const char * _id)
{
   if (strcmp (_id, PingTypeDataReader::_local_id) == 0)
   {
      return TRUE;
   }

   typedef DDS::DataReader NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return TRUE;
   }

   return FALSE;
}

PingTypeDataReader_ptr PingTypeDataReader::_narrow (DDS::Object_ptr p)
{
   PingTypeDataReader_ptr result = NULL;
   if (p && p->_is_a (PingTypeDataReader::_local_id))
   {
      result = dynamic_cast<PingTypeDataReader_ptr> (p);
      result->m_count++;
   }
   return result;
}

PingTypeDataReader_ptr PingTypeDataReader::_unchecked_narrow (DDS::Object_ptr p)
{
   PingTypeDataReader_ptr result;
   result = dynamic_cast<PingTypeDataReader_ptr> (p);
   result->m_count++;
   return result;
}



#if EORB_USE_EXPLICIT_TEMPLATES
template class DDS_DCPSUVLSeq <KeyedPingType, struct KeyedPingTypeSeq_uniq_>;
#endif

const char * KeyedPingTypeTypeSupportInterface::_local_id = "IDL:/KeyedPingTypeTypeSupportInterface:1.0";

KeyedPingTypeTypeSupportInterface_ptr KeyedPingTypeTypeSupportInterface::_duplicate (KeyedPingTypeTypeSupportInterface_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean KeyedPingTypeTypeSupportInterface::_local_is_a (const char * _id)
{
   if (strcmp (_id, KeyedPingTypeTypeSupportInterface::_local_id) == 0)
   {
      return TRUE;
   }

   typedef DDS::TypeSupport NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return TRUE;
   }

   return FALSE;
}

KeyedPingTypeTypeSupportInterface_ptr KeyedPingTypeTypeSupportInterface::_narrow (DDS::Object_ptr p)
{
   KeyedPingTypeTypeSupportInterface_ptr result = NULL;
   if (p && p->_is_a (KeyedPingTypeTypeSupportInterface::_local_id))
   {
      result = dynamic_cast<KeyedPingTypeTypeSupportInterface_ptr> (p);
      result->m_count++;
   }
   return result;
}

KeyedPingTypeTypeSupportInterface_ptr KeyedPingTypeTypeSupportInterface::_unchecked_narrow (DDS::Object_ptr p)
{
   KeyedPingTypeTypeSupportInterface_ptr result;
   result = dynamic_cast<KeyedPingTypeTypeSupportInterface_ptr> (p);
   result->m_count++;
   return result;
}

const char * KeyedPingTypeDataWriter::_local_id = "IDL:/KeyedPingTypeDataWriter:1.0";

KeyedPingTypeDataWriter_ptr KeyedPingTypeDataWriter::_duplicate (KeyedPingTypeDataWriter_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean KeyedPingTypeDataWriter::_local_is_a (const char * _id)
{
   if (strcmp (_id, KeyedPingTypeDataWriter::_local_id) == 0)
   {
      return TRUE;
   }

   typedef DDS::DataWriter NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return TRUE;
   }

   return FALSE;
}

KeyedPingTypeDataWriter_ptr KeyedPingTypeDataWriter::_narrow (DDS::Object_ptr p)
{
   KeyedPingTypeDataWriter_ptr result = NULL;
   if (p && p->_is_a (KeyedPingTypeDataWriter::_local_id))
   {
      result = dynamic_cast<KeyedPingTypeDataWriter_ptr> (p);
      result->m_count++;
   }
   return result;
}

KeyedPingTypeDataWriter_ptr KeyedPingTypeDataWriter::_unchecked_narrow (DDS::Object_ptr p)
{
   KeyedPingTypeDataWriter_ptr result;
   result = dynamic_cast<KeyedPingTypeDataWriter_ptr> (p);
   result->m_count++;
   return result;
}

const char * KeyedPingTypeDataReader::_local_id = "IDL:/KeyedPingTypeDataReader:1.0";

KeyedPingTypeDataReader_ptr KeyedPingTypeDataReader::_duplicate (KeyedPingTypeDataReader_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean KeyedPingTypeDataReader::_local_is_a (const char * _id)
{
   if (strcmp (_id, KeyedPingTypeDataReader::_local_id) == 0)
   {
      return TRUE;
   }

   typedef DDS::DataReader NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return TRUE;
   }

   return FALSE;
}

KeyedPingTypeDataReader_ptr KeyedPingTypeDataReader::_narrow (DDS::Object_ptr p)
{
   KeyedPingTypeDataReader_ptr result = NULL;
   if (p && p->_is_a (KeyedPingTypeDataReader::_local_id))
   {
      result = dynamic_cast<KeyedPingTypeDataReader_ptr> (p);
      result->m_count++;
   }
   return result;
}

KeyedPingTypeDataReader_ptr KeyedPingTypeDataReader::_unchecked_narrow (DDS::Object_ptr p)
{
   KeyedPingTypeDataReader_ptr result;
   result = dynamic_cast<KeyedPingTypeDataReader_ptr> (p);
   result->m_count++;
   return result;
}



