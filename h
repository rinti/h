#!/bin/bash 
case "$1" in
'db')
  echo "Getting a fresh DB"
  dropdb ${PWD##*/} && createdb ${PWD##*/} && heroku pg:backups public-url | xargs curl > latest.dump && pg_restore -d ${PWD##*/} latest.dump --clean --no-acl --no-owner
;;
'x')
  echo "Expiring database"
  heroku pg:backups capture
;;
'aws')
  echo "Exporting AWS settings"
  if [[ "$VIRTUAL_ENV" != "" ]]
  then
    export `heroku config -s | grep ^AWS`
  else
    echo "You're not in a virtualenv."
  fi
;;
esac
