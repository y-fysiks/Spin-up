#include <cmath>
#include <utility>
#include "node.hpp"

#ifndef TARGET_HPP
#define TARGET_HPP

#define visionRadius 15
#define headStartM 8
#define velocityM 2

namespace purePursuit {

    struct Target {
        double velocity = velocityM;
        double headStart = headStartM;

        double xPos = 0;
        double yPos = 0;
        double xh = 0, yh = 0, xd = 0, yd = 0, xoy = 0, d = 0;
        double xTrans = 0, yTrans = 0;
        Node heading;
        
        std::pair<Node, Node> path[128] = { };
        int pathLength = 0;

        int stage = 0, start = 0;
        bool hnorth = true, heast = true, unlocked = true;

        bool atPathEnd = false;

        bool firstLoop = false;

        Target() {}

        void newPath(double xPos_, double yPos_, std::pair<Node, Node> path_[], int pathSize_) {
            firstLoop = true;
            unlocked = true;

            heading = Node(xh, yh);
            pathLength = pathSize_;

            xPos = xPos_;
            yPos = yPos_;

            for (int i = 0; i < 256; i++) {
                if (i < pathLength) {
                    path[i] = path_[i];
                }
            }

            this -> setHeading();
            this -> setHeadStart(visionRadius);

        }

        void updatePosition() {
            if (unlocked) {
                setStage();
                setHeading();
                findRelativePos();
                findTranslation();
                setNSEW();
                if (this -> d > this -> velocity) {
                    standardTranslate();
                }
                if (this -> d < this -> velocity) {
                    xPos = xh;
                    yPos = yh;
                }
            }
        }
        void setHeading() {
            if (stage < pathLength) {
                heading = path[stage].second;
                xh = path[stage].second.xPos;
                yh = path[stage].second.yPos;
            } else {
                atPathEnd = true;
            }
        }

        void findRelativePos() {
            xd = fabs(xPos - xh);
            yd = fabs(yPos - yh);
            d = sqrt(xd * xd + yd * yd);
        }

        void findTranslation() {
            if (yd > 0) {
                xoy = xd / yd;
                xTrans = (xoy * velocity) / sqrt(xoy * xoy + 1);
                yTrans = (velocity) / sqrt(xoy * xoy + 1);
            }
            if (yd < 0.001) {
                xoy = 0;
                xTrans = velocity;
                yTrans = 0;
            }
            if (xd < 0.001) {
                xoy = 1e9;
                xTrans = 0;
                yTrans = velocity;
            }
            
        }

        void setNSEW() {
            if (xPos < xh) {
                heast = true;
            } else {
                heast = false;
            }

            if (yPos < yh) {
                hnorth = false;
            } else {
                hnorth = true;
            }
        }

        void standardTranslate() {
            if (heast) {
                xPos += xTrans;
            } else {
                xPos -= xTrans;
            }

            if (hnorth) {
                yPos -= yTrans;
            } else {
                yPos += yTrans;
            }

        }

        void setStage() {
            if (firstLoop) {
                firstLoop = false;
            } else {
                if (xd == 0 && yd == 0 && stage < pathLength) {
                    stage++;
                }
            }
            if (stage == pathLength) {
                unlocked = false;
            }
        }

        void setHeadStart(double headS) {
            xh = path[0].second.xPos;
            yh = path[0].second.yPos;
            xd = fabs(xPos - xh);
            yd = fabs(yPos - yh);
            if (yd == 0) xoy = 1e9;
            else xoy = xd / yd;
            xTrans = (xoy * headS) / (sqrt(xoy * xoy + 1));
            yTrans = (headS) / (sqrt(xoy * xoy + 1));

            setNSEW();
            standardTranslate();

        }

        void bind(double disp) {
            double transDist = disp - visionRadius;
            xTrans = (xoy * transDist) / (sqrt(xoy * xoy + 1));
            yTrans = transDist / (sqrt(xoy * xoy + 1));

            if (heast) xPos -= xTrans;
            else xPos += xTrans;
            if (hnorth) yPos += yTrans;
            else yPos -= yTrans;
        }

    } ;
}
#endif