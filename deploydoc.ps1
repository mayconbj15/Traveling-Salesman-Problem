$repo_link=((git remote -v | Select-String origin)[0].Line -split "`t| ")[1]

./document.ps1

cd doc/html

git init
git remote add origin $repo_link
git checkout -b gh-pages
git add *
git commit -m "Upload doc"
git push origin gh-pages -f

cd ../..
Remove-Item -Recurse -Force doc
