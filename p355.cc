#include "common.h"
class Twitter {
  public:
    /** Initialize your data structure here. */
    Twitter() { time = 0; }

    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        TwitNode *node = new TwitNode(userId, tweetId, time++);
        if (users.find(userId) == users.end()) {
            users.insert(userId);
            u2unode[userId] = new UserNode(userId);
        }
        UserNode *p = u2unode[userId];
        p->tids.push_back(node);
    }

    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed
     * must be posted by users who the user followed or by the user herself. Tweets must be ordered
     * from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        vector<int> result;
        if (users.find(userId) != users.end()) {
            unordered_set<int> &followees = u2followee[userId];
            priority_queue<pair<TwitNode *, int>, vector<pair<TwitNode *, int>>, TwitNodeCompare> q;
            // include user himself
            vector<int> idx(1 + followees.size(), 0);
            vector<vector<TwitNode *> *> pall; // posts?
            // vector<UserNode*> pall;
            pall.push_back(&(u2unode[userId]->tids));
            for (auto f : followees) {
                pall.push_back(&(u2unode[f]->tids));
            }
            // push one from pall to q;
            for (size_t i = 0; i < pall.size(); ++i) {
                int &index = idx[i];
                if (index < pall[i]->size()) {
                    q.push(make_pair((*(pall[i]))[pall[i]->size() - 1 - index], i));
                    index++;
                }
            }
            while (!q.empty() && result.size() < 10) {
                pair<TwitNode *, int> t = q.top();
                q.pop();
                result.push_back(t.first->tid);
                int from = t.second;
                int &index = idx[from];
                if (index < pall[from]->size()) {
                    q.push(make_pair((*(pall[from]))[pall[from]->size() - 1 - index], from));
                    index++;
                }
            }
        }
        return result;
    }

    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if (followerId == followeeId)
            return;
        // if (!(users.find(followerId) == users.end() && users.find(followeeId) == users.end())) {
        if (true) {
            if (users.find(followeeId) == users.end()) {
                users.insert(followeeId);
                u2unode[followeeId] = new UserNode(followeeId);
            }
            if (users.find(followerId) == users.end()) {
                users.insert(followerId);
                u2unode[followerId] = new UserNode(followerId);
            }
            u2follower[followeeId].insert(followerId);
            u2followee[followerId].insert(followeeId);
        }
    }

    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        if (followerId == followeeId)
            return;
        if (users.find(followeeId) != users.end() && users.find(followerId) != users.end()) {
            u2follower[followeeId].erase(followerId);
            u2followee[followerId].erase(followeeId);
        }
    }

  private:
    struct TwitNode {
        int uid;
        int tid;
        int tstamp;
        TwitNode(int u, int t, int s) : uid(u), tid(t), tstamp(s) {}
    };
    struct TwitNodeCompare {
        bool operator()(const pair<TwitNode *, int> &a, const pair<TwitNode *, int> &b) {
            return (a.first)->tstamp < (b.first)->tstamp;
        }
    };
    struct UserNode {
        int uid;
        vector<TwitNode *> tids; // by user uid
        UserNode(int u) : uid(u) {}
    };

    unordered_set<int> users;
    int time; // to differentiate twitter
    unordered_map<int, UserNode *> u2unode;
    unordered_map<int, unordered_set<int>> u2follower; // who are following uid
    unordered_map<int, unordered_set<int>> u2followee; // who are fllowed by uid
};

int main() {

    Solution s;

    return 0;
}
