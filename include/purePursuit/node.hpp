#ifndef NODE_HPP
#define NODE_HPP

namespace purePursuit {
    struct Node {
        double xPos = 0;
        double yPos = 0;

        Node(double xPos_, double yPos_) {
            xPos = xPos_;
            yPos = yPos_;
        }
        Node() {}
    } ;
}
#endif