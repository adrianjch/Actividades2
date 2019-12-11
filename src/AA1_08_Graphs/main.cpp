#include "GraphD.h"

int main() {
	GraphD g;
	g.Insert({ 1,2 });
	g.Insert({ 3,4 });
	g.Insert({ 2,2 });
	g.Insert({ 2,2 });
	g.Insert({ 2,3 });

	g.Remove({ 2,3 });
	g.Remove({ 2,1 });
	g.Remove({ 5,2 });

	g.Print();
	return 0;
}