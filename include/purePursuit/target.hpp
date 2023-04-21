#include <cmath>
#include <utility>
#include "node.hpp"

#ifndef TARGET_HPP
#define TARGET_HPP

#define visionRadius 25
#define headStartM 20
#define velocityM 10

namespace purePursuit {

    struct Target {
        long double velocity = velocityM;
        long double headStart = headStartM;

        long double xPos = 0;
        long double yPos = 0;
        long double xh = 0, yh = 0, xd = 0, yd = 0, xoy = 0, ds = 0;
        long double xTrans = 0, yTrans = 0;
        Node heading = Node(0, 0);
        
        std::pair<Node, Node> path[128];
        int pathLength = 0;

        int stage = 0, start = 0;
        bool hnorth = true, heast = true, unlocked = false;

        bool atPathEnd = false;

        bool firstLoop = false;

        Target() {}

        void newPath(double xPos_, double yPos_, std::pair<Node, Node> path_[], int pathLength_) {
            firstLoop = true;
            unlocked = true;

            heading = Node(xh, yh);
            pathLength = pathLength_;

            xPos = xPos_;
            yPos = yPos_;
            
            for (int i = 0; i < 128; i++) {
                if (i < pathLength) {
                    path[i] = path_[i];
                }
            }

            setHeading();
            setHeadStart(visionRadius);

        }

        void updatePosition() {
            if (unlocked) {
                setStage();
                setHeading();
                findRelativePos();
                findTranslation();
                setNSEW();
                if (ds > velocity * velocity) {
                    standardTranslate();
                }
                if (ds < velocity * velocity) {
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
            ds = xd * xd + yd * yd;
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
                hnorth = true;
            } else {
                hnorth = false;
            }
        }

        void standardTranslate() {
            if (heast) {
                xPos += xTrans;
            } else {
                xPos -= xTrans;
            }

            if (hnorth) {
                yPos += yTrans;
            } else {
                yPos -= yTrans;
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

        void setHeadStart(long double headS) {
            xh = path[0].second.xPos;
            yh = path[0].second.yPos;
            xd = fabs(xPos - xh);
            yd = fabs(yPos - yh);
            if (yd == 0) xoy = 1e8;
            else xoy = xd / yd;
            xTrans = (xoy * headS) / (sqrt(xoy * xoy + 1));
            yTrans = (headS) / (sqrt(xoy * xoy + 1));

            setNSEW();
            standardTranslate();

        }

        void bind(long double disp) {
            double transDist = disp - visionRadius;
            xTrans = (xoy * transDist) / (sqrt(xoy * xoy + 1));
            yTrans = transDist / (sqrt(xoy * xoy + 1));

            if (heast) xPos -= xTrans;
            else xPos += xTrans;
            if (hnorth) yPos -= yTrans;
            else yPos += yTrans;
        }

    } ;
}
#endif