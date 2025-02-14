require( "config.lazy" )

require( "core.options" )
require( "core.keymaps" )

require( "nvim-treesitter.configs" ).setup {
	ensure_installed = { "c", "lua", "vim", "vimdoc", "query", "python", },
	sync_install = false,
	auto_install = true,
	highlight = {
		enable = true,
	}
}
