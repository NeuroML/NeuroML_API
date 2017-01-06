/// \todo Copyright notice

#ifndef NEURO_ML_CUSTOM_HXX
#define NEURO_ML_CUSTOM_HXX

namespace neuroml2
{
/**
 * @brief Class corresponding to the %Morphology schema type.
 *
 * Standalone element which is usually inside a single cell, but could be
 * outside and referenced by id.
 *
 * This class extends the automatically-generated definition by adding a
 * num_segments() method.
 *
 * @nosubgrouping
 */
class Morphology: public Morphology_base
{
public:
    // Our additions to the class

    /**
     * @return The number of segments present.
     */
    unsigned num_segments() const;

    // Constructor signatures etc. copied from the auto-generated base class.

    /**
     * @name Constructors
     */
    //@{
    /**
     * @brief Create an instance from the ultimate base and
     * initializers for required elements and attributes.
     */
    Morphology(const id_type&);

    /**
     * @brief Create an instance from a DOM element.
     *
     * @param e A DOM element to extract the data from.
     * @param f Flags to create the new instance with.
     * @param c A pointer to the object that will contain the new
     * instance.
     */
    Morphology(const ::xercesc::DOMElement& e,
               ::xml_schema::flags f = 0,
               ::xml_schema::container* c = 0);

    /**
     * @brief Copy constructor.
     *
     * @param x An instance to make a copy of.
     * @param f Flags to create the copy with.
     * @param c A pointer to the object that will contain the copy.
     *
     * For polymorphic object models use the @c _clone function instead.
     */
    Morphology(const Morphology& x,
               ::xml_schema::flags f = 0,
               ::xml_schema::container* c = 0);

    /**
     * @brief Copy the instance polymorphically.
     *
     * @param f Flags to create the copy with.
     * @param c A pointer to the object that will contain the copy.
     * @return A pointer to the dynamically allocated copy.
     *
     * This function ensures that the dynamic type of the instance is
     * used for copying and should be used for polymorphic object
     * models instead of the copy constructor.
     */
    virtual Morphology*
    _clone(::xml_schema::flags f = 0,
           ::xml_schema::container* c = 0) const;

    /**
     * @brief Copy assignment operator.
     *
     * @param x An instance to make a copy of.
     * @return A reference to itself.
     *
     * For polymorphic object models use the @c _clone function instead.
     */
    Morphology&
    operator=(const Morphology& x);

    //@}

    /**
     * @brief Destructor.
     */
    virtual
    ~Morphology();
};

/**
 * @brief Class corresponding to the %Segment schema type.
 *
 * @nosubgrouping
 */
class Segment: public Segment_base
{
public:
    // Our additions to the class

    /**
     * @return The length of this segment.
     */
    double length() const;

    /**
     * @return The volume of this segment.
     */
    double volume() const;

    /**
     * @return The surface area of this segment.
     */
    double surface_area() const;

    // Constructor signatures etc. copied from the auto-generated base class.

    /**
     * @name Constructors
     */
    //@{
    /**
     * @brief Create an instance from the ultimate base and
     * initializers for required elements and attributes.
     */
    Segment(const id_type&,
            const distal_type&);

    /**
     * @brief Create an instance from the ultimate base and
     * initializers for required elements and attributes
     * (::std::unique_ptr version).
     *
     * This constructor will try to use the passed values directly
     * instead of making copies.
     */
    Segment(const id_type&,
            ::std::unique_ptr<distal_type>);

    /**
     * @brief Create an instance from a DOM element.
     *
     * @param e A DOM element to extract the data from.
     * @param f Flags to create the new instance with.
     * @param c A pointer to the object that will contain the new
     * instance.
     */
    Segment(const ::xercesc::DOMElement& e,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

    /**
     * @brief Copy constructor.
     *
     * @param x An instance to make a copy of.
     * @param f Flags to create the copy with.
     * @param c A pointer to the object that will contain the copy.
     *
     * For polymorphic object models use the @c _clone function instead.
     */
    Segment(const Segment& x,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

    /**
     * @brief Copy the instance polymorphically.
     *
     * @param f Flags to create the copy with.
     * @param c A pointer to the object that will contain the copy.
     * @return A pointer to the dynamically allocated copy.
     *
     * This function ensures that the dynamic type of the instance is
     * used for copying and should be used for polymorphic object
     * models instead of the copy constructor.
     */
    virtual Segment*
    _clone(::xml_schema::flags f = 0,
           ::xml_schema::container* c = 0) const;

    /**
     * @brief Copy assignment operator.
     *
     * @param x An instance to make a copy of.
     * @return A reference to itself.
     *
     * For polymorphic object models use the @c _clone function instead.
     */
    Segment&
    operator=(const Segment& x);

    //@}

    /**
     * @brief Destructor.
     */
    virtual
    ~Segment();
};
}

#endif // NEURO_ML_CUSTOM_HXX