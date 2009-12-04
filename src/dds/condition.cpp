#include <dds/condition.hpp>

/////////////////////////////////////////////////////////////////////////////
dds::ActiveConditionImpl::~ActiveConditionImpl() {
}

/////////////////////////////////////////////////////////////////////////////
dds::ActiveCondition::ActiveCondition(ActiveConditionImpl* aci) :
	cond_(aci) {
}
dds::ActiveCondition::~ActiveCondition() {
}


bool
dds::ActiveCondition::operator==(const ActiveCondition& other)
{
	return cond_ == other.cond_;
}

/////////////////////////////////////////////////////////////////////////////
dds::ActiveReadConditionImpl::~ActiveReadConditionImpl() {
}

/////////////////////////////////////////////////////////////////////////////
dds::ActiveReadCondition::ActiveReadCondition(dds::ActiveReadConditionImpl* arc)
: ActiveCondition(arc), pcond_(arc)
{ }

dds::ActiveReadCondition::ActiveReadCondition()
: ActiveCondition(0), pcond_(0)
{

}

dds::ActiveReadCondition::~ActiveReadCondition() {
}

/////////////////////////////////////////////////////////////////////////////
dds::ActiveQueryConditionImpl::~ActiveQueryConditionImpl() {
}

/////////////////////////////////////////////////////////////////////////////
dds::ActiveQueryCondition::ActiveQueryCondition(dds::ActiveQueryConditionImpl* qcond)
	: ActiveReadCondition(qcond), pcond_(qcond)
	{ }

dds::ActiveQueryCondition::ActiveQueryCondition()
	: ActiveReadCondition(0), pcond_(0)
	{ }

dds::ActiveQueryCondition::~ActiveQueryCondition() {
}
