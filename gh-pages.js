var ghpages = require('gh-pages');

ghpages.publish(
    'dist',
    {
        branch: 'master',
        repo: 'https://github.com/BlockchainCommons/lifehash-web.git',
        user: {
            name: 'Wolf McNally',
            email: 'wolf@wolfmcnally.com'
        }
    },
    () => {
        console.log('Deploy Complete!')
    }
)
