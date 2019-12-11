#include <memory>
#include <vector>
#include <iostream>

#include "TextInEllipse.h"
#include "Helix.h"

int main()
{
    std::vector<std::shared_ptr<Shape>> arr{
                std::make_shared<Circle>(10.0, Point{3,4}),
                std::make_shared<Helix>(Point{0,0}, 3, Point{3,4}),
                std::make_shared<Text>("The plain text", Point{3,4}),
                std::make_shared<Ellipse>(Point{3,4}, 5, 6),
                std::make_shared<TextInEllipse>("It's a text")
    };

    for (auto &ptr: arr) {
        std::cout << *ptr.get();
    }

    std::cout << "\nPURE MAGIC\n\n";

    dynamic_cast<Circle*>(arr[0].get())->setRad(48);
    dynamic_cast<Helix*>(arr[1].get())->setM({42,42});
    dynamic_cast<Text*>(arr[2].get())->setText("Wow, the text has changed");
    dynamic_cast<Ellipse*>(arr[3].get())->setHorizontalRadius(444);
    dynamic_cast<TextInEllipse*>(arr[4].get())->setText("Now it's THE text");


    for (auto &ptr: arr) {
        std::cout << *ptr.get();
    }
}