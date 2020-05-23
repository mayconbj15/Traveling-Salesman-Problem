repo_link=$(git remote -v | grep origin | cut -d' ' -f1 | cut -f2 | head -n1)

./document.sh

cd doc/html

git init
git remote add origin $repo_link
git checkout -b gh-pages
git add *
git commit -m "Upload doc"
git push origin gh-pages -f

cd ../..
rm -rf doc
