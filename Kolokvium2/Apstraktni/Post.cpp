//
// Created by Teodora on 30.5.2024.
//
#include<iostream>
#include<string>
using namespace std;

class Post{
protected:
    string avtor;
    string sodrzina;
    bool fotografija;
    int like;
public:
    Post(string avtor="", string sodrzina="", bool fotografija=false, int like=0){
        this->avtor = avtor;
        this->sodrzina = sodrzina;
        this->fotografija = fotografija;
        this->like = like;
    }

    virtual double popularity() = 0;

    virtual void print(){
        cout<<"Username: "<<avtor<<endl;
        cout<<"Content: "<<sodrzina<<endl;
        if(fotografija){
            cout<<"With photo"<<endl;
        }else{
            cout<<"Without photo"<<endl;
        }
        cout<<"Likes: "<<like<<" ";
    }

    bool operator>=(Post &p){
        return popularity() >= p.popularity();
    }

    friend double mostPopularPostWithPhoto(Post **posts, int n);
};

class FacebookPost : public Post{
private:
    int shares;
public:
    FacebookPost(string avtor="", string sodrzina="", bool fotografija=false, int like=0, int shares=0)
    : Post(avtor, sodrzina, fotografija, like){
        this->shares = shares;
    }

    double popularity(){
        double proizvod = like*shares;
        if(fotografija){
            proizvod *= 1.2;
        }
        return proizvod;
    }

    void print() override{
        cout<<"FacebookPost"<<endl;
        Post::print();
        cout<<"Shares: "<<shares<<endl;
        cout<<"Popularity: "<<popularity()<<endl;
    }
};

class TwitterPost : public Post{
private:
    int retweets;
    int replies;
public:
    TwitterPost(string avtor="", string sodrzina="", bool fotografija=false, int like=0, int retweets=0, int replies=0)
    : Post(avtor, sodrzina, fotografija, like){
        this->retweets = retweets;
        this->replies = replies;
    }

    double popularity(){
        double proizvod = like*retweets*replies;
        if(fotografija){
            proizvod *= 1.1;
        }
        if(sodrzina.find('#crypto') != -1){
            proizvod *= 1.2;
        }
        return proizvod;
    }

    void print() override{
        cout<<"TwitterPost"<<endl;
        Post::print();
        cout<<"Retweets: "<<retweets<<" Replies: "<<replies<<endl;
        cout<<"Popularity: "<<popularity()<<endl;
    }
};

double mostPopularPostWithPhoto(Post **posts, int n){
    double mostPopular = -1;
    for (int i = 0; i < n; ++i) {
        if(posts[i]->fotografija && posts[i]->popularity() > mostPopular){
            mostPopular = posts[i]->popularity();
        }
    }
    return mostPopular;
}

Post * leastPopularTwitterPost(Post **posts, int n){
    Post *leastPopular = posts[0];
    for (int i = 0; i < n; ++i) {
        if(dynamic_cast<TwitterPost*>(posts[i])){
            if(posts[i]->popularity() < leastPopular->popularity()){
                leastPopular = posts[i];
            }
        }
    }
    return leastPopular;
}

Post *readFbPost() {
    return nullptr;
}

Post *readTwPost() {
    return nullptr;
}

Post **readMultiplePosts(int *pInt) {
    return nullptr;
}

int main() {
    int testCase;

    cin >> testCase;

    if (testCase == 1) {
        cout << "Test FacebookPost" << endl;
        Post *post = readFbPost();
        cout << "Popularity: " << post->popularity() << endl;
        post->print();
    } else if (testCase == 2) {
        cout << "Test TwitterPost" << endl;
        Post *post = readTwPost();
        cout << "Popularity: " << post->popularity() << endl;
        post->print();
    } else if (testCase == 3) {
        cout << "Test operator >=" << endl;
        int n;
        Post **posts = readMultiplePosts(&n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    if ((*posts[i]) >= (*posts[j])) {
                        cout << i << " >= " << j << endl;
                    } else {
                        cout << i << " < " << j << endl;
                    }
                }
            }
        }
    } else {
        int n;
        Post **posts = readMultiplePosts(&n);
        for (int i = 0; i < n; i++) {
            posts[i]->print();
            cout << endl;
        }
        cout << "The most popular post with photo has a popularity of: " << mostPopularPostWithPhoto(posts, n) << endl;

        cout << "The least popular twitter post is: " << endl;
        Post * result = leastPopularTwitterPost(posts,n);
        if (result== nullptr){
            cout << "None";
        } else {
            result->print();
        }
    }
    return 0;
}