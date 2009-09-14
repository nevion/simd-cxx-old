#include <simd/condition.hpp>

/////////////////////////////////////////////////////////////////////////////
simd::ActiveConditionImpl::~ActiveConditionImpl() {
}

/////////////////////////////////////////////////////////////////////////////
simd::ActiveCondition::ActiveCondition(ActiveConditionImpl* aci) :
	cond_(aci) {
}
simd::ActiveCondition::~ActiveCondition() {
}


bool
simd::ActiveCondition::operator==(const ActiveCondition& other)
{
	return cond_ == other.cond_;
}

/////////////////////////////////////////////////////////////////////////////
simd::ActiveReadConditionImpl::~ActiveReadConditionImpl() {
}

/////////////////////////////////////////////////////////////////////////////
simd::ActiveReadCondition::ActiveReadCondition(simd::ActiveReadConditionImpl* arc)
: ActiveCondition(arc), pcond_(arc)
{ }

simd::ActiveReadCondition::ActiveReadCondition()
: ActiveCondition(0), pcond_(0)
{

}

simd::ActiveReadCondition::~ActiveReadCondition() {
}

/////////////////////////////////////////////////////////////////////////////
simd::ActiveQueryConditionImpl::~ActiveQueryConditionImpl() {
}

/////////////////////////////////////////////////////////////////////////////
simd::ActiveQueryCondition::ActiveQueryCondition(simd::ActiveQueryConditionImpl* qcond)
	: ActiveReadCondition(qcond), pcond_(qcond)
	{ }

simd::ActiveQueryCondition::ActiveQueryCondition()
	: ActiveReadCondition(0), pcond_(0)
	{ }

simd::ActiveQueryCondition::~ActiveQueryCondition() {
}
