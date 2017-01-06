/// \todo Copyright notice etc.

#include "NeuroML_v2beta4.hxx"

#include <cmath>
#include <string>

namespace neuroml2
{

// Morphology methods

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

// Segment methods

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

// Connection methods

unsigned Connection::_get_cell_id(const std::string& id_string) const
{
    int id;
    std::string::size_type pos = id_string.find('[');
    if (pos != std::string::npos)
    {
        // The id is between square brackets
        std::string::size_type end_pos = id_string.find(']', pos);
        assert(end_pos != std::string::npos);
        id = stoi(id_string.substr(pos+1, end_pos-pos-1));
    }
    else
    {
        // The id is after the second / (and before any third /, if present)
        pos = id_string.find('/');
        assert(pos != std::string::npos);
        pos = id_string.find('/', pos+1);
        assert(pos != std::string::npos);
        std::string::size_type end_pos = id_string.find('/', pos+1);
        if (end_pos == std::string::npos)
        {
            id = stoi(id_string.substr(pos+1));
        }
        else
        {
            id = stoi(id_string.substr(pos+1, end_pos-pos-1));
        }
    }
    assert(id >= 0);
    return static_cast<unsigned>(id);
}

unsigned Connection::get_pre_cell_id() const
{
    return _get_cell_id(preCellId());
}

unsigned Connection::get_post_cell_id() const
{
    return _get_cell_id(postCellId());
}

Connection::Connection(const id_type& id, const preCellId_type& pre, const postCellId_type& post)
    : Connection_base(id, pre, post)
{
}

Connection::Connection(const ::xercesc::DOMElement& e, ::xml_schema::flags f, ::xml_schema::container* c)
    : Connection_base(e, f, c)
{
}

Connection::Connection(const Connection& x, ::xml_schema::flags f, ::xml_schema::container* c)
    : Connection_base(x, f, c)
{
}

Connection* Connection::_clone(::xml_schema::flags f, ::xml_schema::container* c) const
{
    return new Connection(*this, f, c);
}

Connection::~Connection()
{
}

}

// Streaming operators

#include <iostream>

namespace neuroml2
{

::std::ostream&
operator<<(::std::ostream& o, const Connection& c)
{
    o << ::std::endl << "Connection " << c.id() << ": "
      << c.get_pre_cell_id() << " -> " << c.get_post_cell_id();
    o << static_cast<const ::neuroml2::Connection_base&>(c);

    return o;
}


}

