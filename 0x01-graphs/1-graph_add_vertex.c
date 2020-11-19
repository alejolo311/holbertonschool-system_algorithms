#include "graphs.h"
/**
 * graph_add_vertex - add a new vertex to a graph
 * @graph: the graph
 * @str: the content of the new vertes
 * Return: a vertex pointer on succes or NULL
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *vertex, *vertex_head;

	if (graph == NULL || str == NULL)
		return (NULL);
	vertex_head = graph->vertices;
	while (vertex_head != NULL)
	{
		if (strcmp(str, vertex_head->content) == 0)
			return (NULL);
		if (vertex_head->next)
			vertex_head = vertex_head->next;
		else
			break;
	}
	vertex = malloc(sizeof(vertex_t));
	if (vertex == NULL)
		return (NULL);

	vertex->content = strdup(str);
	vertex->index = graph->nb_vertices;
	vertex->nb_edges = 0, vertex->edges = NULL;

	if (vertex_head)
		vertex_head->next = vertex;
	else
		graph->vertices = vertex;

	graph->nb_vertices++;
	return (vertex);
}
