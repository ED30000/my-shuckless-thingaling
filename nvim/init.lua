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

vim.api.nvim_create_autocmd("Bufenter", {
	pattern = "*",
	callback = function()
		local dir = vim.fn.expand("%:p:h")
		vim.cmd("cd " .. dir)
		vim.cmd("pwd")
	end,
})
