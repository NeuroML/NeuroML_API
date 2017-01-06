// Quick test function for the xsd-generated C++ mapping.

#include <iostream>
#include <fstream>
#include <memory>

#include "NeuroML_v2beta4.hxx"

const std::string schema_path("file://" SCHEMA_PATH);

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Syntax: " << argv[0] << " <file.nml>" << std::endl;
        return 1;
    }

    try
    {
        std::cout << "Parsing path " << argv[1] << std::endl;
        // We enforce use of our schema for validation, no matter what the document says
        ::xml_schema::properties props;
        props.schema_location("http://www.neuroml.org/schema/neuroml2", schema_path);
        std::unique_ptr<neuroml2::NeuroMLDocument> model(neuroml2::neuroml(argv[1], 0, props));

        // Required attributes (or child elements with single cardinality) can just be accessed directly.
        std::cout << "Parsed model id " << model->id() << std::endl;

        // Optional content has an _optional type wrapping it, with present() and get() methods.
        neuroml2::NeuroMLDocument::metaid_optional metaid = model->metaid();
        if (metaid.present())
        {
            std::cout << "Meta id is " << metaid.get() << std::endl;
            // You can also treat it like a pointer.
            // We often don't bother assigning to a variable, because the type names get long.
            std::cout << "Meta id via pointer: " << *(model->metaid()) << std::endl;
        }

        // Where more than one of a child can be present, they're wrapped in a
        // sequence type which behaves just like a std::vector.
        neuroml2::NeuroMLDocument::cell_sequence cells = model->cell();
        std::cout << "Number of cells: " << cells.size() << std::endl;
        for (neuroml2::NeuroMLDocument::cell_iterator it = model->cell().begin();
             it != model->cell().end();
             ++it)
        {
            std::cout << "  id: " << it->id() << std::endl;
            // Check that our added method works
            if (it->morphology().present())
            {
                std::cout << "    Number of morphology segments: " << it->morphology()->num_segments() << std::endl;
                assert(it->morphology() == it->morphology()); // Check that comparison operators still apply

                // Check extra methods for segments
                if (!it->morphology()->segment().empty())
                {
                    neuroml2::Segment seg1 = it->morphology()->segment().at(1);
                    std::cout << "    Segment 1:" << std::endl;
                    std::cout << "      length=" << seg1.length()
                              << ", volume=" << seg1.volume()
                              << ", surface area=" << seg1.surface_area() << std::endl;
                }
            }
        }

        // We can also serialise back to a file (or other output stream)
        if (argc > 2)
        {
            std::cout << "Serialising to " << argv[2] << std::endl;
            xml_schema::namespace_infomap map;
            map[""].name = "http://www.neuroml.org/schema/neuroml2";
            map[""].schema = schema_path;
            std::ofstream f(argv[2]);
            neuroml2::neuroml(f, *model, map);
        }

        // And textual summaries of the tree also come 'for free'
        if (argc > 3)
        {
            std::cout << "Dumping summary to " << argv[3] << std::endl;
            std::ofstream f(argv[3]);
            f << *model;
        }
    }
    catch (const xml_schema::exception& e)
    {
        std::cerr << "XSD error:" << std::endl << e << std::endl;
        return 1;
    }
    return 0;
}
