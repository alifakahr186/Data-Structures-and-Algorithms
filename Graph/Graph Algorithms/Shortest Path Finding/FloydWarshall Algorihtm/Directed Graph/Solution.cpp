//dist[i][j]= min(dist[i][j],dist[i][k]+dist[k][j])

/*
it is array write orginal value or id 
for dist = 0 1 2 3
for i = [0 1 2 3][0 1 2 3][0 1 2 3][0 1 2 3]   according to the vertex size
for j = 0 1 2 3
*/

//for exmaple
/*
dist[0][3] > dist[0][2] + dist[2][3]
[1][4] > [1][2] + [2][4]
INF > 9 + 2
INF > 11
*/