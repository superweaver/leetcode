#include "common.h"
class Solution {
public:
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        // assume root is root of tree,
        // choose any of node as root at this moment
        // at this moment!!!!
        // distanceSum[i] is the distanceSum of node i to other nodes in subtree rooted at node i
        // count[i] is the number of nodes in the subtree rooted at node i
        // it is clear that count[root] = sum(count[root's child]) + 1 (root itself)
        // then distanceSum[root] = sum(distanceSum[root's children]) + sum(count[root's children])
        // why does the second equation hold?
        // distanceSum[root] = sum (distance of root to every subnode)
        // let's say subnode j, the path from root to j, must pass through one of root's children
        // distance of root to every subnode = distance of root to one of root' children (==1) +
        // distance of this root's child to every subnode
        // sum of first term == sum(count[root's children])
        // sum of second term == sum(distanceSum[root's children])

        // once we finish update distanceSum and count array
        // result += distanceSum[root], at this moment, other nodes's distanceSum is only a subtree!
        // it is not done yet
        // pick any of root's children, let's say node j, promote it as new root
        // distanceSum[j] = distanceSum[root] + (N-count[j]) - (count[j]);
        // there are count[j] nodes(j's subtree) 1 step closer
        // and there are N-count[j] nodes 1 step farther
        // note there is no need to update count array
        // to avoid circular traversal, use visited unordered_set
        // (in this tree structure, there is no circular structure)
        vector<vector<int>> graph(N);
        for(auto& e: edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        //vector<int> visited(N, 0);
        vector<int> distanceSum(N, 0);
        vector<int> count(N, 0);
        // post order to update distanceSum and count
        postOrder(0, -1, graph, distanceSum, count);
        // at this moment, only distanceSum at root is completed
        preOrder(0, -1, graph, distanceSum, count);
        return distanceSum;
    }
private:
    void postOrder(int root, int pre,  vector<vector<int> >& graph, vector<int>& distanceSum,
                   vector<int>& count)
    {
        for(auto child: graph[root]) {
            if (child != pre) {
                postOrder(child, root, graph, distanceSum, count);
                count[root] += count[child];
                distanceSum[root] += distanceSum[child] + count[child];
            }
        }
        count[root]++;
        return;
    }
    void preOrder(int root, int pre, vector<vector<int> >& graph, vector<int>& distanceSum,
                   vector<int>& count)
    {
        for(auto child: graph[root]) {
            if(child != pre) {
                distanceSum[child] = distanceSum[root] + (distanceSum.size() - count[child]) - (count[child]);
                preOrder(child, root, graph, distanceSum, count);
            }
        }
    }
};

class Solution_copy {
public:
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        // assume root is root of tree,
        // choose any of node as root at this moment
        // at this moment!!!!
        // distanceSum[i] is the distanceSum of node i to other nodes in subtree rooted at node i
        // count[i] is the number of nodes in the subtree rooted at node i
        // it is clear that count[root] = sum(count[root's child]) + 1 (root itself)
        // then distanceSum[root] = sum(distanceSum[root's children]) + sum(count[root's children])
        //
        // why does the second equation hold?
        // distanceSum[root] = sum (distance of root to every subnode)
        // let's say subnode j, the path from root to j, must pass through one of root's children
        // distance of root to every subnode = distance of root to one of root' children (==1) +
        // distance of this root's child to every subnode
        //
        // sum of first term == sum(count[root's children])
        // sum of second term == sum(distanceSum[root's children])

        // once we finish update distanceSum and count array
        // result += distanceSum[root], at this moment, other nodes's distanceSum is only a subtree!
        // it is not done yet
        //
        // pick any of root's children, let's say node j, promote it as new root
        //
        // distanceSum[j] = distanceSum[root] + (N-count[j]) - (count[j]);
        //
        // there are count[j] nodes(j's subtree) 1 step closer
        // and there are N-count[j] nodes 1 step farther
        //
        // note there is no need to update count array
        //
        // to avoid circular traversal, use visited unordered_set
        //
        // (in this tree structure, there is no circular structure)
        vector<vector<int>> graph(N);
        for(auto& e: edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        vector<int> visited(N, 0);
        vector<int> distanceSum(N, 0);
        vector<int> count(N, 0);

        // post order to update distanceSum and count
        postOrder(0, graph, distanceSum, count, visited);

        // at this moment, only distanceSum of root(0) is completed
        visited = vector<int>(N, 0);
        // update other' distanceSum
        preOrder(0, graph, distanceSum, count, visited);

        return distanceSum;
    }
private:
    void postOrder(int root, vector<vector<int> >& graph, vector<int>& distanceSum,
                   vector<int>& count, vector<int> visited)
    {
        if (visited[root] != 0) {
            return ;
        }
        visited[root] = 1;
        for(auto child: graph[root]) {
            if (!visited[child]) {
                postOrder(child, graph, distanceSum, count, visited);
                count[root] += count[child];
                distanceSum[root] += distanceSum[child] + count[child];
            }
        }
        count[root]++;
        visited[root] = 2;
        return;
    }
    void preOrder(int root, vector<vector<int> >& graph, vector<int>& distanceSum,
                   vector<int>& count, vector<int> visited)
    {
        if (visited[root] != 0) {
            return;
        }
        visited[root] = 1;
        for(auto child: graph[root]) {
            if(!visited[child]) {
                // finish child before going child's child
                distanceSum[child] = distanceSum[root] + (distanceSum.size() - count[child]) - (count[child]);
                preOrder(child, graph, distanceSum, count, visited);
            }
        }
        visited[root] = 2;
    }
};



int main() {

	Solution s;

	return 0;
}
