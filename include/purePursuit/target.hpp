#include <cmath>
#include <utility>
#include "node.hpp"

#ifndef TARGET_HPP
#define TARGET_HPP

#define visionRadius 15
#define headStartM 13
#define velocityM 0.8

namespace purePursuit {

    struct Target {
        double velocity = velocityM;
        double headStart = headStartM;

        double xPos = 0;
        double yPos = 0;
        double xd = 0, yd = 0, xoy = 0, ds = 0;
        double xTrans = 0, yTrans = 0;
        Node endpoint = Node(0, 0);
        
        std::pair<Node, Node> path[128];
        int pathLength = 0;

        int stage = 0;
        bool hnorth = true, heast = true, unlocked = false;

        bool atPathEnd = false;

        bool firstLoop = false;

        Target() {}

        void newPath(std::pair<Node, Node> path_[], int pathLength_) {
            firstLoop = true;
            unlocked = true;

            stage = 0;

            //endpoint = Node(xh, yh);
            pathLength = pathLength_;
            
            for (int i = 0; i < 128; i++) {
                if (i < pathLength) {
                    path[i] = path_[i];
                }
            }

            xPos = path[0].first.xPos;
            yPos = path[0].first.yPos;

            //setStage();

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
                    xPos = endpoint.xPos;
                    yPos = endpoint.yPos;
                }
            }
        }
        void setHeading() {
            if (stage < pathLength) {
                endpoint = path[stage].second;
            } else {
                atPathEnd = true;
            }
        }

        void findRelativePos() {
            xd = fabs(xPos - endpoint.xPos);
            yd = fabs(yPos - endpoint.yPos);
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
            if (xPos < endpoint.xPos) {
                heast = true;
            } else {
                heast = false;
            }

            if (yPos < endpoint.yPos) {
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

        void setHeadStart(double headS) {
            xd = fabs(xPos - endpoint.xPos);
            yd = fabs(yPos - endpoint.yPos);
            if (yd == 0) xoy = 1e8;
            else xoy = xd / yd;
            xTrans = (xoy * headS) / (sqrt(xoy * xoy + 1));
            yTrans = (headS) / (sqrt(xoy * xoy + 1));

            setNSEW();

            if (xTrans > xd || yTrans > yd) {
                xTrans = xd;
                yTrans = yd;
                
            }
            standardTranslate();

        }

        void bind(double disp) {
            double transDist = disp - visionRadius;
            double xTrans1 = (xoy * transDist) / (sqrt(xoy * xoy + 1));
            double yTrans1 = transDist / (sqrt(xoy * xoy + 1));

            if (heast) {
                xPos -= xTrans1;
            } else {
                xPos += xTrans1;
            }

            if (hnorth) {
                yPos -= yTrans1;
            } else {
                yPos += yTrans1;
            }

        }

    } ;
}
#endif