#include "GraphD.h"

int main() {
	GraphD g;
	g.Insert({ 1,2 });
	g.Insert({ 3,1 });
	g.Insert({ 2,2 });
	g.Insert({ 4,2 });
	g.Print();
	return 0;
}