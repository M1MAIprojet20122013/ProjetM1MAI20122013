#include "plot.h"

static FILE* h_gnuplot;
static uint plot_id = 0;

void init_gnuplot()
{
	printf("Initializing gnuplot...\n");
	h_gnuplot = popen("gnuplot --persist", "w");
	if (h_gnuplot == NULL)
	{
		printf("Initializing gnuplot [FAILED]\n");
	}
	else
	{	fprintf(h_gnuplot, "unset key \n\n");
		printf("Initializing gnuplot [  OK  ]\n");
	}
}

void plot_from(const char* filename, const char* options)
{
	if (plot_id == 0)
	{
		fprintf(h_gnuplot, "plot '");
	}
	else
	{
		fprintf(h_gnuplot, "replot '");
	}
	fprintf(h_gnuplot,"%s", filename);
	fprintf(h_gnuplot, "' ");
	fprintf(h_gnuplot,"%s", options);
	fprintf(h_gnuplot, "\n\n");
	fflush(h_gnuplot);
}

void plot(const Point* points, uint length, const char* options)
{
	char filename[15];
	sprintf(filename, "/tmp/plot-%i", plot_id);
	FILE* f = fopen(filename, "w");
	if (f == NULL)
	{
		fprintf(stderr, "[ ERROR ] cannot save dataset to a temp file");
	}
	else
	{
		uint i;
		for (i=0;i<length;++i)
		{
			fprintf(f, "%f %f %f\n", points[i].x, points[i].y, points[i].z);
		}
		fclose(f);
		plot_from(filename, options);
		++plot_id;
	}
}
void plot_vector( const Point p1, const Point p2, const Vector normal, const char* options)
{
		char filename[15];
	sprintf(filename, "/tmp/plot-%i", plot_id);
	FILE* f = fopen(filename, "w");
	if (f == NULL)
	{
		fprintf(stderr, "[ ERROR ] cannot save dataset to a temp file");
	}
	else
	{
		fprintf(f, "%f %f %f %f\n", (p1.x+p2.x)/2, (p1.y+p2.y)/2, normal.x,normal.y);
		fclose(f);
		fprintf(h_gnuplot, "replot '");
		fprintf(h_gnuplot,"%s", filename);
		fprintf(h_gnuplot, "' ");	
		fprintf(h_gnuplot,"%s", options);
		fprintf(h_gnuplot, "\n\n");
		fflush(h_gnuplot);
		++plot_id;
	}
}

int close_gnuplot()
{
	return pclose(h_gnuplot);
}
