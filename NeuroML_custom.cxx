/// \todo Copyright notice etc.

#include "NeuroML_v2beta4.hxx"

#include <cmath>

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

double Segment::length() const
{
    assert(proximal().present());
    double x = proximal()->x() - distal().x();
    double y = proximal()->y() - distal().y();
    double z = proximal()->z() - distal().z();

    return sqrt(x*x + y*y + z*z);
}

double Segment::volume() const
{
    assert(proximal().present());
    double prox_rad = proximal()->diameter() / 2.0;
    double dist_rad = distal().diameter() / 2.0;

    return (M_PI/3.0) * length() * (prox_rad*prox_rad + dist_rad*dist_rad + prox_rad*dist_rad);
}

double Segment::surface_area() const
{
    assert(proximal().present());
    double prox_rad = proximal()->diameter() / 2.0;
    double dist_rad = distal().diameter() / 2.0;
    double rad_diff = prox_rad-dist_rad;
    double len = length();

    return M_PI * (prox_rad + dist_rad) * sqrt(rad_diff*rad_diff + len*len);
}

Segment::Segment(const id_type& id, const distal_type& d)
    : Segment_base(id, d)
{
}

Segment::Segment(const id_type& id, ::std::unique_ptr<distal_type> d)
    : Segment_base(id, std::move(d))
{
}

Segment::Segment(const ::xercesc::DOMElement& e, ::xml_schema::flags f, ::xml_schema::container* c)
    : Segment_base(e, f, c)
{
}

Segment::Segment(const Segment& x, ::xml_schema::flags f, ::xml_schema::container* c)
    : Segment_base(x, f, c)
{
}

Segment* Segment::_clone(::xml_schema::flags f, ::xml_schema::container* c) const
{
    return new Segment(*this, f, c);
}

Segment& Segment::operator =(const Segment& x)
{
    if (this != &x)
    {
        static_cast<Segment_base&>(*this) = x;
    }
    return *this;
}

Segment::~Segment()
{
}

}
