/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 01/05/2020
 */
#include "ConverterController.hpp"

using namespace std;

Command back_converter() {
    return Command{
            "Goes back to start.",
            [] (const Interface&) { return 0; }
    };
}

Command how_to(const Interface& interface) {
    return Command{
        "Shows how to convert images.",
     [&interface] (const Interface&) {
            interface.print("First, you have to specify the folder in which the program will search for images "
                            "using command \"folder\", for example \"/home/users/john/imgs\".\n"
                            "After that, enter the command \"convert\" and a folder with converted images "
                            "will be saved in the folder you have entered before.\n");
            return 1;
        }
    };
}

Command folder(const Interface& interface) {
    return Command{
        "Specify the folder with images.",
        [&interface] (const Interface&) {
            //todo: set folder location to m_Location, test file types and print the number of valid images
            return 1;
        }
    };
}

ConverterController::ConverterController(const Interface& interface) : Controller(interface) {
    m_Commands.emplace("back", back_converter());
    m_Commands.emplace("howto", how_to(m_Interface));
    m_Commands.emplace("folder", folder(m_Interface));

    m_Welcome = "[ You're in the converter ]\n";
}
