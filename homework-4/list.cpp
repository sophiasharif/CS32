void listAll(string path, const File* f)  // two-parameter overload
{
    // base case: not a directory
    if (f->files() == nullptr) {
        cout << path << endl;
        return;
    }
    
    cout <<  path + "/" << endl;
    
    for (vector<File*>::const_iterator i = f->files()->begin(); i != f->files()->end(); i++) {
        listAll( path + "/" + (*i)->name(), *i);
    }
}
