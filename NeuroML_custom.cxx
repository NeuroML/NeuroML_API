/// \todo Copyright notice etc.

#include "NeuroML_v2beta4.hxx"

namespace neuroml2
{

unsigned Morphology::num_segments() const
{
	return segment().size();
}

Morphology::Morphology(const id_type& id)
	: Morphology_base(id)
{
}

Morphology::Morphology(const ::xercesc::DOMElement& e,
					   ::xml_schema::flags f,
					   ::xml_schema::container* c)
	: Morphology_base(e, f, c)
{
}

Morphology::Morphology(const Morphology& x,
					   ::xml_schema::flags f,
					   ::xml_schema::container* c)
	: Morphology_base(x, f, c)
{
}

Morphology* Morphology::_clone(::xml_schema::flags f,
							   ::xml_schema::container* c) const
{
	return new Morphology(*this, f, c);
}

Morphology& Morphology::operator =(const Morphology& x)
{
    if (this != &x)
    {
    	static_cast<Morphology_base&>(*this) = x;
    }
    return *this;
}

Morphology::~Morphology()
{
}

}
