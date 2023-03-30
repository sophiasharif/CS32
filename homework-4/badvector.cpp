void removeBad(vector<Movie*>& v)
{
    for (auto i = v.begin(); i != v.end(); i++) {
        auto mp = *i;
        if (mp->rating() < 50) {
            delete mp;
            i = v.erase(i);
            i--;
        }
    }
}

