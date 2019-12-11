#include <memory>

#include "SPGraph/SPGraph.h"

#include "shapes/TextInEllipse.h"
#include "shapes/Helix.h"

bool shapeComp( const std::shared_ptr<Shape>& left, const std::shared_ptr<Shape>& right  )
{
    return (*left).getCentral().x == (*right).getCentral().x;
}

int main() {
    SPGraph< std::shared_ptr<Shape> > s(std::make_shared<Text>(Text{"s", Point{1,1}}), std::make_shared<Circle>(Circle{}));
    SPGraph< std::shared_ptr<Shape> > s1(std::make_shared<Helix>(Helix{Point{42,42}, 4, Point{24,24}}), std::make_shared<Ellipse>(Ellipse{}));
    SPGraph< std::shared_ptr<Shape> > s2(std::make_shared<TextInEllipse>(TextInEllipse{"s1", Point{4,5}}), std::make_shared<TextInEllipse>(TextInEllipse{"s1^2", Point{123123,123134}}));

    s.setComparator(shapeComp);

    //made of 2 vertices
    try{
        s.pop(s.begin());
    } catch (const SPException<std::shared_ptr<Shape>>& e)
    {
        std::cout << e.what() << '\n';
    }

    s.seriesComposition(s1);
    s.seriesComposition(s2);

    SPGraph< std::shared_ptr<Shape> > ss(std::make_shared<Text>(Text{"ss", Point{1,1}}), std::make_shared<Circle>(Circle{}));
    SPGraph< std::shared_ptr<Shape> > sss(std::make_shared<Helix>(Helix{Point{42,42}, 4, Point{24,24}}), std::make_shared<Ellipse>(Ellipse{}));
    SPGraph< std::shared_ptr<Shape> > ssss(std::make_shared<TextInEllipse>(TextInEllipse{"ssss", Point{4,5}}), std::make_shared<TextInEllipse>(TextInEllipse{"ssss^2", Point{123123,123134}}));

    ss.seriesComposition(sss);
    ss.seriesComposition(ssss);

    s.parallelComposition(ss);

    //made of 6 vertices

    //source have 2 children
    try{
        s.pop(s.begin());
    } catch (const SPException<std::shared_ptr<Shape>>& e)
    {
        std::cout << e.what() << '\n';
    }

    //terminal have 2 parent
    try{
        s.pop(s.end());
    } catch (const SPException<std::shared_ptr<Shape>>& e)
    {
        std::cout << e.what() << '\n';
    }

    std::cout << s.size() << " is still 6 \n";

    //std::cout << *(*s.begin()).get();

    try{
        SPiterator< std::shared_ptr<Shape> > it(s.begin());

        while(true)
            std::cout << *(++it).operator*().get();

    } catch (const SPinvalidIt<std::shared_ptr<Shape> >& e)
    {
        std::cout << e.what() << '\n';
    }
    return 0;
}